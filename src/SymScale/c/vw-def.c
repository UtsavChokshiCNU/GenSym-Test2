/* vw-def.c
 * Input file:  view-def.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "vw-def.h"


Object The_type_description_of_access_error = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_access_errors, Qchain_of_available_access_errors);

DEFINE_VARIABLE_WITH_SYMBOL(Access_error_count, Qaccess_error_count);

Object Chain_of_available_access_errors_vector = UNBOUND;

/* ACCESS-ERROR-STRUCTURE-MEMORY-USAGE */
Object access_error_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(92,0);
    temp = Access_error_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ACCESS-ERROR-COUNT */
Object outstanding_access_error_count()
{
    Object def_structure_access_error_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(92,1);
    gensymed_symbol = IFIX(Access_error_count);
    def_structure_access_error_variable = Chain_of_available_access_errors;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_access_error_variable))
	goto end_loop;
    def_structure_access_error_variable = 
	    ISVREF(def_structure_access_error_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ACCESS-ERROR-1 */
Object reclaim_access_error_1(access_error)
    Object access_error;
{
    Object temp, svref_arg_2;

    x_note_fn_call(92,2);
    inline_note_reclaim_cons(access_error,Nil);
    temp = ISVREF(Chain_of_available_access_errors_vector,
	    IFIX(Current_thread_index));
    SVREF(access_error,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_access_errors_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = access_error;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ACCESS-ERROR */
Object reclaim_structure_for_access_error(access_error)
    Object access_error;
{
    x_note_fn_call(92,3);
    return reclaim_access_error_1(access_error);
}

static Object Qg2_defstruct_structure_name_access_error_g2_struct;  /* g2-defstruct-structure-name::access-error-g2-struct */

/* MAKE-PERMANENT-ACCESS-ERROR-STRUCTURE-INTERNAL */
Object make_permanent_access_error_structure_internal()
{
    Object def_structure_access_error_variable;
    Object defstruct_g2_access_error_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(92,4);
    def_structure_access_error_variable = Nil;
    atomic_incff_symval(Qaccess_error_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_access_error_variable = Nil;
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
	defstruct_g2_access_error_variable = the_array;
	SVREF(defstruct_g2_access_error_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_access_error_g2_struct;
	def_structure_access_error_variable = 
		defstruct_g2_access_error_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_access_error_variable);
}

/* MAKE-ACCESS-ERROR-1 */
Object make_access_error_1(access_error_name,access_error_particulars)
    Object access_error_name, access_error_particulars;
{
    Object def_structure_access_error_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(92,5);
    def_structure_access_error_variable = 
	    ISVREF(Chain_of_available_access_errors_vector,
	    IFIX(Current_thread_index));
    if (def_structure_access_error_variable) {
	svref_arg_1 = Chain_of_available_access_errors_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_access_error_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_access_error_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_access_error_g2_struct;
    }
    else
	def_structure_access_error_variable = 
		make_permanent_access_error_structure_internal();
    inline_note_allocate_cons(def_structure_access_error_variable,Nil);
    SVREF(def_structure_access_error_variable,FIX((SI_Long)1L)) = 
	    access_error_name;
    SVREF(def_structure_access_error_variable,FIX((SI_Long)2L)) = 
	    access_error_particulars;
    return VALUES_1(def_structure_access_error_variable);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "ACCESS-ERROR: ~(~a~)" */

static Object string_constant_1;   /* " where:~%" */

static Object string_constant_2;   /* "  ~a = ~NV~%" */

/* MAKE-DEFAULT-TEXT-STRING-FOR-ACCESS-ERROR */
Object make_default_text_string_for_access_error(access_error)
    Object access_error;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object particulars_qm, name, value, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(92,6);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
	      3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      particulars_qm = ISVREF(access_error,(SI_Long)2L);
	      tformat(2,string_constant,ISVREF(access_error,(SI_Long)1L));
	      if (particulars_qm)
		  tformat(1,string_constant_1);
	      name = Nil;
	      value = Nil;
	      ab_loop_list_ = particulars_qm;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	    next_loop:
	      name = CAR(ab_loop_list_);
	      temp = CDR(ab_loop_list_);
	      value = CAR(temp);
	      tformat(3,string_constant_2,name,value);
	      ab_loop_list_ = CDDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qmissing_implied_attribute;  /* missing-implied-attribute */

static Object Qitem;               /* item */

static Object string_constant_3;   /* "~NF" */

static Object Qsymbolic_value;     /* symbolic-value */

/* MAKE-MISSING-IMPLIED-ATTRIBUTE-ERROR-MESSAGE */
Object make_missing_implied_attribute_error_message(item,new_value)
    Object item, new_value;
{
    Object temp;

    x_note_fn_call(92,7);
    temp = make_access_error_1(Qmissing_implied_attribute,
	    gensym_list_4(Qitem,tformat_text_string(2,string_constant_3,
	    item),Qsymbolic_value,new_value));
    return VALUES_1(temp);
}

static Object Qconclude_no_value_in_non_variable;  /* conclude-no-value-in-non-variable */

/* MAKE-CONCLUDE-NO-VALUE-INTO-NON-VARIABLE-ERROR-MESSAGE */
Object make_conclude_no_value_into_non_variable_error_message(place)
    Object place;
{
    Object temp;

    x_note_fn_call(92,8);
    temp = make_access_error_1(Qconclude_no_value_in_non_variable,
	    gensym_list_2(Qitem,tformat_text_string(2,string_constant_3,
	    place)));
    return VALUES_1(temp);
}

static Object Qno_such_class_error;  /* no-such-class-error */

static Object Qab_class_name;      /* class-name */

/* MAKE-NO-SUCH-CLASS-ERROR-MESSAGE */
Object make_no_such_class_error_message(class_name)
    Object class_name;
{
    Object temp;

    x_note_fn_call(92,9);
    temp = make_access_error_1(Qno_such_class_error,
	    gensym_list_2(Qab_class_name,class_name));
    return VALUES_1(temp);
}

static Object Qconclude_into_non_variable_or_parameter;  /* conclude-into-non-variable-or-parameter */

static Object Qitem_class;         /* item-class */

/* MAKE-CONCLUDE-INTO-NON-V-OR-P-ERROR-MESSAGE */
Object make_conclude_into_non_v_or_p_error_message(item)
    Object item;
{
    Object temp;

    x_note_fn_call(92,10);
    temp = tformat_text_string(2,string_constant_3,item);
    temp = make_access_error_1(Qconclude_into_non_variable_or_parameter,
	    gensym_list_4(Qitem,temp,Qitem_class,ISVREF(ISVREF(item,
	    (SI_Long)1L),(SI_Long)1L)));
    return VALUES_1(temp);
}

static Object Qattribute;          /* attribute */

static Object string_constant_4;   /* "~NS" */

static Object Qitem_in_attribute;  /* item-in-attribute */

static Object Qinactive_item_in_attribute;  /* inactive-item-in-attribute */

/* MAKE-INACTIVE-ITEM-IN-ATTRIBUTE-ERROR-MESSAGE */
Object make_inactive_item_in_attribute_error_message(slot_description,
	    class_description,item,slot_value)
    Object slot_description, class_description, item, slot_value;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, temp;

    x_note_fn_call(92,11);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qattribute;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = tformat_text_string(3,string_constant_4,
	    slot_description,class_description);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qitem;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = tformat_text_string(2,string_constant_3,item);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qitem_in_attribute;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = tformat_text_string(2,string_constant_3,slot_value);
    M_CAR(gensymed_symbol_1) = car_new_value;
    temp = make_access_error_1(Qinactive_item_in_attribute,gensymed_symbol);
    return VALUES_1(temp);
}

static Object string_constant_5;   /* "~NA" */

/* REALLY-GENERAL-TWRITE */
Object really_general_twrite(x)
    Object x;
{
    Object car_1, cdr_1, temp;
    char temp_1;

    x_note_fn_call(92,12);
    if (CONSP(x)) {
	car_1 = M_CAR(x);
	cdr_1 = M_CDR(x);
	if (CONSP(cdr_1)) {
	    temp = M_CAR(cdr_1);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(M_CAR(x));
    else
	return tformat_text_string(2,string_constant_5,x);
}

static Object Qattribute_name;     /* attribute-name */

static Object Qab_class;           /* class */

static Object Qlt_none_gt;         /* <none> */

static Object Qattribute_or_structure;  /* attribute-or-structure */

static Object Qattribute_access_on_non_frame;  /* attribute-access-on-non-frame */

/* MAKE-ATTRIBUTE-ACCESS-ON-NON-FRAME-ERROR */
Object make_attribute_access_on_non_frame_error(would_be_item,slot_name,
	    class_qualifier_qm)
    Object would_be_item, slot_name, class_qualifier_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, temp;

    x_note_fn_call(92,13);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qattribute_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = slot_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qab_class;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = class_qualifier_qm;
    if (car_new_value);
    else
	car_new_value = Qlt_none_gt;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qattribute_or_structure;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = really_general_twrite(would_be_item);
    M_CAR(gensymed_symbol_1) = car_new_value;
    temp = make_access_error_1(Qattribute_access_on_non_frame,gensymed_symbol);
    return VALUES_1(temp);
}

static Object Qvirtual_attribute_name;  /* virtual-attribute-name */

static Object Qno_such_virtual_attribute;  /* no-such-virtual-attribute */

/* MAKE-NO-SUCH-VIRTUAL-ATTRIBUTE-ERROR-MESSAGE */
Object make_no_such_virtual_attribute_error_message(item,name)
    Object item, name;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, temp;

    x_note_fn_call(92,14);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qvirtual_attribute_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qitem;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = tformat_text_string(2,string_constant_3,item);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qitem_class;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    temp = make_access_error_1(Qno_such_virtual_attribute,gensymed_symbol);
    return VALUES_1(temp);
}

Object Class_subscriptions_kbprop = UNBOUND;

Object The_type_description_of_class_subscriptions = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_class_subscriptionss, Qchain_of_available_class_subscriptionss);

DEFINE_VARIABLE_WITH_SYMBOL(Class_subscriptions_count, Qclass_subscriptions_count);

Object Chain_of_available_class_subscriptionss_vector = UNBOUND;

/* CLASS-SUBSCRIPTIONS-STRUCTURE-MEMORY-USAGE */
Object class_subscriptions_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(92,15);
    temp = Class_subscriptions_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-SUBSCRIPTIONS-COUNT */
Object outstanding_class_subscriptions_count()
{
    Object def_structure_class_subscriptions_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(92,16);
    gensymed_symbol = IFIX(Class_subscriptions_count);
    def_structure_class_subscriptions_variable = 
	    Chain_of_available_class_subscriptionss;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_class_subscriptions_variable))
	goto end_loop;
    def_structure_class_subscriptions_variable = 
	    ISVREF(def_structure_class_subscriptions_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CLASS-SUBSCRIPTIONS-1 */
Object reclaim_class_subscriptions_1(class_subscriptions)
    Object class_subscriptions;
{
    Object temp, svref_arg_2;

    x_note_fn_call(92,17);
    inline_note_reclaim_cons(class_subscriptions,Nil);
    temp = ISVREF(Chain_of_available_class_subscriptionss_vector,
	    IFIX(Current_thread_index));
    SVREF(class_subscriptions,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_class_subscriptionss_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = class_subscriptions;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-SUBSCRIPTIONS */
Object reclaim_structure_for_class_subscriptions(class_subscriptions)
    Object class_subscriptions;
{
    x_note_fn_call(92,18);
    return reclaim_class_subscriptions_1(class_subscriptions);
}

static Object Qg2_defstruct_structure_name_class_subscriptions_g2_struct;  /* g2-defstruct-structure-name::class-subscriptions-g2-struct */

/* MAKE-PERMANENT-CLASS-SUBSCRIPTIONS-STRUCTURE-INTERNAL */
Object make_permanent_class_subscriptions_structure_internal()
{
    Object def_structure_class_subscriptions_variable;
    Object defstruct_g2_class_subscriptions_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(92,19);
    def_structure_class_subscriptions_variable = Nil;
    atomic_incff_symval(Qclass_subscriptions_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_class_subscriptions_variable = Nil;
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
	defstruct_g2_class_subscriptions_variable = the_array;
	SVREF(defstruct_g2_class_subscriptions_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_class_subscriptions_g2_struct;
	def_structure_class_subscriptions_variable = 
		defstruct_g2_class_subscriptions_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_class_subscriptions_variable);
}

/* MAKE-CLASS-SUBSCRIPTIONS-1 */
Object make_class_subscriptions_1()
{
    Object def_structure_class_subscriptions_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(92,20);
    def_structure_class_subscriptions_variable = 
	    ISVREF(Chain_of_available_class_subscriptionss_vector,
	    IFIX(Current_thread_index));
    if (def_structure_class_subscriptions_variable) {
	svref_arg_1 = Chain_of_available_class_subscriptionss_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_class_subscriptions_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_class_subscriptions_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_class_subscriptions_g2_struct;
    }
    else
	def_structure_class_subscriptions_variable = 
		make_permanent_class_subscriptions_structure_internal();
    inline_note_allocate_cons(def_structure_class_subscriptions_variable,Nil);
    SVREF(def_structure_class_subscriptions_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_class_subscriptions_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_class_subscriptions_variable);
}

Object The_type_description_of_class_subscription = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_class_subscriptions, Qchain_of_available_class_subscriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Class_subscription_count, Qclass_subscription_count);

Object Chain_of_available_class_subscriptions_vector = UNBOUND;

/* CLASS-SUBSCRIPTION-STRUCTURE-MEMORY-USAGE */
Object class_subscription_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(92,21);
    temp = Class_subscription_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CLASS-SUBSCRIPTION-COUNT */
Object outstanding_class_subscription_count()
{
    Object def_structure_class_subscription_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(92,22);
    gensymed_symbol = IFIX(Class_subscription_count);
    def_structure_class_subscription_variable = 
	    Chain_of_available_class_subscriptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_class_subscription_variable))
	goto end_loop;
    def_structure_class_subscription_variable = 
	    ISVREF(def_structure_class_subscription_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CLASS-SUBSCRIPTION-1 */
Object reclaim_class_subscription_1(class_subscription)
    Object class_subscription;
{
    Object temp, svref_arg_2;

    x_note_fn_call(92,23);
    inline_note_reclaim_cons(class_subscription,Nil);
    temp = ISVREF(Chain_of_available_class_subscriptions_vector,
	    IFIX(Current_thread_index));
    SVREF(class_subscription,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_class_subscriptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = class_subscription;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLASS-SUBSCRIPTION */
Object reclaim_structure_for_class_subscription(class_subscription)
    Object class_subscription;
{
    x_note_fn_call(92,24);
    return reclaim_class_subscription_1(class_subscription);
}

static Object Qg2_defstruct_structure_name_class_subscription_g2_struct;  /* g2-defstruct-structure-name::class-subscription-g2-struct */

/* MAKE-PERMANENT-CLASS-SUBSCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_class_subscription_structure_internal()
{
    Object def_structure_class_subscription_variable;
    Object defstruct_g2_class_subscription_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(92,25);
    def_structure_class_subscription_variable = Nil;
    atomic_incff_symval(Qclass_subscription_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_class_subscription_variable = Nil;
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
	defstruct_g2_class_subscription_variable = the_array;
	SVREF(defstruct_g2_class_subscription_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_class_subscription_g2_struct;
	def_structure_class_subscription_variable = 
		defstruct_g2_class_subscription_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_class_subscription_variable);
}

/* MAKE-CLASS-SUBSCRIPTION-1 */
Object make_class_subscription_1(class_subscription_denotation,
	    class_subscription_inner_item_index,
	    class_subscription_representation)
    Object class_subscription_denotation, class_subscription_inner_item_index;
    Object class_subscription_representation;
{
    Object def_structure_class_subscription_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(92,26);
    def_structure_class_subscription_variable = 
	    ISVREF(Chain_of_available_class_subscriptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_class_subscription_variable) {
	svref_arg_1 = Chain_of_available_class_subscriptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_class_subscription_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_class_subscription_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_class_subscription_g2_struct;
    }
    else
	def_structure_class_subscription_variable = 
		make_permanent_class_subscription_structure_internal();
    inline_note_allocate_cons(def_structure_class_subscription_variable,Nil);
    SVREF(def_structure_class_subscription_variable,FIX((SI_Long)1L)) = 
	    class_subscription_denotation;
    SVREF(def_structure_class_subscription_variable,FIX((SI_Long)2L)) = 
	    class_subscription_inner_item_index;
    SVREF(def_structure_class_subscription_variable,FIX((SI_Long)3L)) = 
	    class_subscription_representation;
    return VALUES_1(def_structure_class_subscription_variable);
}

Object Representation_callback_remote_procedure_name_prop = UNBOUND;

static Object Qrepresentation_callback_remote_procedure_name;  /* representation-callback-remote-procedure-name */

/* DEMAND-REPRESENTATION-CALLBACK-REMOTE-PROCEDURE-NAME */
Object demand_representation_callback_remote_procedure_name(remote_procedure_name_thing)
    Object remote_procedure_name_thing;
{
    Object temp;

    x_note_fn_call(92,27);
    if (SYMBOLP(remote_procedure_name_thing)) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(remote_procedure_name_thing),
		Qrepresentation_callback_remote_procedure_name);
	if (temp);
	else
	    temp = mutate_global_property(remote_procedure_name_thing,
		    make_remote_procedure_name_function(remote_procedure_name_thing),
		    Qrepresentation_callback_remote_procedure_name);
    }
    else
	temp = remote_procedure_name_thing;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Javalink_notification_versions, Qjavalink_notification_versions);

DEFINE_VARIABLE_WITH_SYMBOL(Notification_data_version_map, Qnotification_data_version_map);

DEFINE_VARIABLE_WITH_SYMBOL(Current_lookup_data, Qcurrent_lookup_data);

/* JAVALINK-VERSIONING-MAKE-ARG-LIST-COPY */
Object javalink_versioning_make_arg_list_copy(arg_list,subscription_handle)
    Object arg_list, subscription_handle;
{
    Object return_list, arg, ab_loop_list_, temp;

    x_note_fn_call(92,28);
    return_list = Nil;
    arg = Nil;
    ab_loop_list_ = arg_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = FIXNUMP(arg) || arg && SYMBOLP(arg) || SIMPLE_VECTOR_P(arg) ? 
	    arg : copy_if_evaluation_value_1(arg);
    return_list = eval_cons_1(temp,return_list);
    goto next_loop;
  end_loop:
    return_list = eval_cons_1(subscription_handle,return_list);
    temp = nreverse(return_list);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* RECLAIM-JAVALINK-VERSIONED-CALL-DATA-ARG-LISTS */
Object reclaim_javalink_versioned_call_data_arg_lists(arg_lists)
    Object arg_lists;
{
    Object arg_list, ab_loop_list_, arg, ab_loop_list__1;

    x_note_fn_call(92,29);
    arg_list = Nil;
    ab_loop_list_ = arg_lists;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    arg = Nil;
    ab_loop_list__1 = arg_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    arg = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !(FIXNUMP(arg) || SYMBOLP(arg) || SIMPLE_VECTOR_P(arg)))
	reclaim_if_evaluation_value_1(arg);
    goto next_loop_1;
  end_loop_1:;
    reclaim_eval_list_1(arg_list);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(arg_lists);
    return VALUES_1(Qnil);
}

Object The_type_description_of_javalink_versioned_call_data = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_javalink_versioned_call_datas, Qchain_of_available_javalink_versioned_call_datas);

DEFINE_VARIABLE_WITH_SYMBOL(Javalink_versioned_call_data_count, Qjavalink_versioned_call_data_count);

Object Chain_of_available_javalink_versioned_call_datas_vector = UNBOUND;

/* JAVALINK-VERSIONED-CALL-DATA-STRUCTURE-MEMORY-USAGE */
Object javalink_versioned_call_data_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(92,30);
    temp = Javalink_versioned_call_data_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-JAVALINK-VERSIONED-CALL-DATA-COUNT */
Object outstanding_javalink_versioned_call_data_count()
{
    Object def_structure_javalink_versioned_call_data_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(92,31);
    gensymed_symbol = IFIX(Javalink_versioned_call_data_count);
    def_structure_javalink_versioned_call_data_variable = 
	    Chain_of_available_javalink_versioned_call_datas;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_javalink_versioned_call_data_variable))
	goto end_loop;
    def_structure_javalink_versioned_call_data_variable = 
	    ISVREF(def_structure_javalink_versioned_call_data_variable,
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

/* RECLAIM-JAVALINK-VERSIONED-CALL-DATA-1 */
Object reclaim_javalink_versioned_call_data_1(javalink_versioned_call_data)
    Object javalink_versioned_call_data;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(92,32);
    inline_note_reclaim_cons(javalink_versioned_call_data,Nil);
    structure_being_reclaimed = javalink_versioned_call_data;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_javalink_versioned_call_data_arg_lists(ISVREF(javalink_versioned_call_data,
	      (SI_Long)2L));
      SVREF(javalink_versioned_call_data,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_javalink_versioned_call_datas_vector,
	    IFIX(Current_thread_index));
    SVREF(javalink_versioned_call_data,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_javalink_versioned_call_datas_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = javalink_versioned_call_data;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-JAVALINK-VERSIONED-CALL-DATA */
Object reclaim_structure_for_javalink_versioned_call_data(javalink_versioned_call_data)
    Object javalink_versioned_call_data;
{
    x_note_fn_call(92,33);
    return reclaim_javalink_versioned_call_data_1(javalink_versioned_call_data);
}

static Object Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct;  /* g2-defstruct-structure-name::javalink-versioned-call-data-g2-struct */

/* MAKE-PERMANENT-JAVALINK-VERSIONED-CALL-DATA-STRUCTURE-INTERNAL */
Object make_permanent_javalink_versioned_call_data_structure_internal()
{
    Object def_structure_javalink_versioned_call_data_variable;
    Object defstruct_g2_javalink_versioned_call_data_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(92,34);
    def_structure_javalink_versioned_call_data_variable = Nil;
    atomic_incff_symval(Qjavalink_versioned_call_data_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_javalink_versioned_call_data_variable = Nil;
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
	defstruct_g2_javalink_versioned_call_data_variable = the_array;
	SVREF(defstruct_g2_javalink_versioned_call_data_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct;
	def_structure_javalink_versioned_call_data_variable = 
		defstruct_g2_javalink_versioned_call_data_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_javalink_versioned_call_data_variable);
}

/* MAKE-JAVALINK-VERSIONED-CALL-DATA-1 */
Object make_javalink_versioned_call_data_1()
{
    Object def_structure_javalink_versioned_call_data_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(92,35);
    def_structure_javalink_versioned_call_data_variable = 
	    ISVREF(Chain_of_available_javalink_versioned_call_datas_vector,
	    IFIX(Current_thread_index));
    if (def_structure_javalink_versioned_call_data_variable) {
	svref_arg_1 = Chain_of_available_javalink_versioned_call_datas_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_javalink_versioned_call_data_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_javalink_versioned_call_data_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct;
    }
    else
	def_structure_javalink_versioned_call_data_variable = 
		make_permanent_javalink_versioned_call_data_structure_internal();
    inline_note_allocate_cons(def_structure_javalink_versioned_call_data_variable,
	    Nil);
    SVREF(def_structure_javalink_versioned_call_data_variable,
	    FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_javalink_versioned_call_data_variable);
}

/* JAVALINK-VERSIONED-CALL-DATA-SENDP */
Object javalink_versioned_call_data_sendp(call_data)
    Object call_data;
{
    Object temp;

    x_note_fn_call(92,36);
    temp = ISVREF(call_data,(SI_Long)2L);
    return VALUES_1(temp);
}

/* MAKE-JAVALINK-VERSIONED-DATA */
Object make_javalink_versioned_data(version)
    Object version;
{
    Object data;

    x_note_fn_call(92,37);
    data = make_javalink_versioned_call_data_1();
    SVREF(data,FIX((SI_Long)1L)) = version;
    return VALUES_1(data);
}

/* JAVALINK-VERSIONED-CALL-DATA-EVALUATED-P */
Object javalink_versioned_call_data_evaluated_p(call_data_or_primitive)
    Object call_data_or_primitive;
{
    Object temp;

    x_note_fn_call(92,38);
    temp = SIMPLE_VECTOR_P(call_data_or_primitive) ? 
	    (EQ(ISVREF(call_data_or_primitive,(SI_Long)0L),
	    Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct) 
	    ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* JAVALINK-VERSIONED-CALL-DATA-GET-VERSION */
Object javalink_versioned_call_data_get_version(data_symbol_or_fixnum)
    Object data_symbol_or_fixnum;
{
    Object temp;

    x_note_fn_call(92,39);
    if (SIMPLE_VECTOR_P(data_symbol_or_fixnum) && 
	    EQ(ISVREF(data_symbol_or_fixnum,(SI_Long)0L),
	    Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct))
	temp = ISVREF(data_symbol_or_fixnum,(SI_Long)1L);
    else if (EQ(T,data_symbol_or_fixnum) || FIXNUMP(data_symbol_or_fixnum))
	temp = data_symbol_or_fixnum;
    else
	temp = cerror((SI_Long)3L,"shouldn\'t be here",
		"Bad version data in notification-data-version-map ~s~%",
		data_symbol_or_fixnum);
    return VALUES_1(temp);
}

/* JAVALINK-VERSIONING-RECLAIM-EVALUATED-VERSION-BODIES */
Object javalink_versioning_reclaim_evaluated_version_bodies(notification_data_version_map)
    Object notification_data_version_map;
{
    Object data, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(92,40);
    PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
	    0);
      data = Nil;
      ab_loop_list_ = Notification_data_version_map;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      data = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (SIMPLE_VECTOR_P(data) && EQ(ISVREF(data,(SI_Long)0L),
	      Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct))
	  reclaim_javalink_versioned_call_data_1(data);
      goto next_loop;
    end_loop:
      reclaim_gensym_list_1(Notification_data_version_map);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* SEND-VERSIONED-WS-NOTIFICATION-INTERNAL */
Object send_versioned_ws_notification_internal(notification_type,item,data)
    Object notification_type, item, data;
{
    Object arg_lists, new_arg_lists_end, svref_arg_1;

    x_note_fn_call(92,41);
    if (v5_tw_item_like_p(item)) {
	if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))
	    item = 
		    get_or_make_connection_frame_and_activate_if_appropriate(item);
	arg_lists = ISVREF(Current_lookup_data,(SI_Long)2L);
	new_arg_lists_end = eval_cons_1(eval_list_3(notification_type,item,
		data),Nil);
	arg_lists = arg_lists ? nconc2(arg_lists,new_arg_lists_end) : 
		new_arg_lists_end;
	svref_arg_1 = Current_lookup_data;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = arg_lists;
    }
    return VALUES_1(Nil);
}

static Object Qsocket;             /* socket */

/* RECLAIM-REPRESENTATION-ADDRESS-VALUE */
Object reclaim_representation_address_value(address,gensymed_symbol)
    Object address, gensymed_symbol;
{
    Object name, value, ab_loop_list_, temp;

    x_note_fn_call(92,42);
    name = Nil;
    value = Nil;
    ab_loop_list_ = address;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    if ( !EQ(name,Qsocket))
	reclaim_slot_value(value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    reclaim_slot_value_list_1(address);
    return VALUES_1(Nil);
}

/* RECLAIM-REPRESENTED-FRAME-VALUE */
Object reclaim_represented_frame_value(frame,representation)
    Object frame, representation;
{
    x_note_fn_call(92,43);
    return VALUES_1(Nil);
}

Object Local_pseudo_socket = UNBOUND;

static Object Qframe_representations;  /* frame-representations */

/* MAKE-REPRESENTATION */
Object make_representation(icp_socket,represented_frame,representation_class)
    Object icp_socket, represented_frame, representation_class;
{
    Object representation, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value, gensym_push_modify_macro_arg;

    x_note_fn_call(92,44);
    representation = make_frame(representation_class);
    slot_value_push_modify_macro_arg = representation;
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = ISVREF(represented_frame,(SI_Long)9L);
    svref_new_value = slot_value_cons_1(car_1,cdr_1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(represented_frame,Qframe_representations);
    SVREF(represented_frame,FIX((SI_Long)9L)) = svref_new_value;
    ISVREF(representation,(SI_Long)9L) = represented_frame;
    if ( !EQ(icp_socket,Local_pseudo_socket)) {
	gensym_push_modify_macro_arg = representation;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(icp_socket,(SI_Long)39L);
	svref_new_value = gensym_cons_1(car_1,cdr_1);
	SVREF(icp_socket,FIX((SI_Long)39L)) = svref_new_value;
    }
    return VALUES_1(representation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_representation_handle_hash_vector_109_vectors, Qavailable_representation_handle_hash_vector_109_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_representation_handle_hash_vector_109_vectors, Qcount_of_representation_handle_hash_vector_109_vectors);

Object Available_representation_handle_hash_vector_109_vectors_vector = UNBOUND;

/* REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTOR-MEMORY-USAGE */
Object representation_handle_hash_vector_109_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(92,45);
    temp = Count_of_representation_handle_hash_vector_109_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)109L)));
    return VALUES_1(temp);
}

/* OUT-REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTORS */
Object out_representation_handle_hash_vector_109_vectors()
{
    Object temp;

    x_note_fn_call(92,46);
    temp = 
	    FIXNUM_MINUS(Count_of_representation_handle_hash_vector_109_vectors,
	    length(Available_representation_handle_hash_vector_109_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTOR-INTERNAL */
Object make_permanent_representation_handle_hash_vector_109_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(92,47);
    atomic_incff_symval(Qcount_of_representation_handle_hash_vector_109_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)109L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-REPRESENTATION-HANDLE-HASH-VECTOR */
Object make_representation_handle_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(92,48);
    if (ISVREF(Available_representation_handle_hash_vector_109_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_representation_handle_hash_vector_109_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_representation_handle_hash_vector_109_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_representation_handle_hash_vector_109_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_representation_handle_hash_vector_109_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_representation_handle_hash_vector_109_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-REPRESENTATION-HANDLE-HASH-VECTOR */
Object reclaim_representation_handle_hash_vector(representation_handle_hash_vector_109_vector)
    Object representation_handle_hash_vector_109_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(92,49);
    svref_arg_1 = 
	    Available_representation_handle_hash_vector_109_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = representation_handle_hash_vector_109_vector;
    temp = 
	    ISVREF(Available_representation_handle_hash_vector_109_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-REPRESENTATION-HANDLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_representation_handle_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(92,50);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-REPRESENTATION-HANDLE-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_representation_handle_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(92,51);
    IDENTITY(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_representation_handle_tree_for_hash_skip_list_entry = UNBOUND;

/* CLEAR-REPRESENTATION-HANDLE-TREE */
Object clear_representation_handle_tree(representation_handle_tree_for_hash_skip_list)
    Object representation_handle_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, old_entry;
    Object result;

    x_note_fn_call(92,52);
    head = M_CAR(M_CDR(representation_handle_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(representation_handle_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),key_qm,
	    representation_handle_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),key_qm);
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	IDENTITY(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(representation_handle_tree_for_hash_skip_list);
}

static Object Qrepresentation_handle_tree_for_hash;  /* representation-handle-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-REPRESENTATION-HANDLE-TABLE */
Object make_representation_handle_table()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(92,53);
    new_vector = make_representation_handle_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)109L)
	goto end_loop;
    tail = 
	    make_representation_handle_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_representation_handle_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qrepresentation_handle_tree_for_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-REPRESENTATION-HANDLE */
Object flatten_representation_handle(representation_handle_hash_table)
    Object representation_handle_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(92,54);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)109L)
	goto end_loop;
    subtree = ISVREF(representation_handle_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-REPRESENTATION-HANDLE */
Object clear_representation_handle(representation_handle_hash_table)
    Object representation_handle_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(92,55);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)109L)
	goto end_loop;
    clear_representation_handle_tree(ISVREF(representation_handle_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-REPRESENTATION-HANDLE */
Object reclaim_representation_handle(representation_handle_hash_table)
    Object representation_handle_hash_table;
{
    Object representation_handle_tree_for_hash_skip_list, head, tail;
    Object element_qm, key_qm, old_entry, last_1, next_qm, temp, svref_arg_2;
    Object temp_1;
    SI_Long index_1;
    Object result;

    x_note_fn_call(92,56);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)109L)
	goto end_loop;
    representation_handle_tree_for_hash_skip_list = 
	    ISVREF(representation_handle_hash_table,index_1);
    head = M_CAR(M_CDR(representation_handle_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(representation_handle_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),key_qm,
	    representation_handle_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),key_qm);
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	IDENTITY(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(representation_handle_tree_for_hash_skip_list) = Nil;
    M_CADR(representation_handle_tree_for_hash_skip_list) = Nil;
    M_CAR(representation_handle_tree_for_hash_skip_list) = Nil;
    if (representation_handle_tree_for_hash_skip_list) {
	last_1 = representation_handle_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = representation_handle_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    representation_handle_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(representation_handle_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_representation_handle_hash_vector(representation_handle_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(The_representation_handle_hashtable, Qthe_representation_handle_hashtable);

/* REPRESENTATION-HANDLE-GETHASH */
Object representation_handle_gethash(handle)
    Object handle;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(92,57);
    gensymed_symbol = IFIX(handle);
    temp = The_representation_handle_hashtable;
    temp_1 = gensymed_symbol % (SI_Long)109L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = handle;
    key_hash_value = gensymed_symbol;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
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
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value) {
	if (EQ(key_value,ISVREF(curr,(SI_Long)2L)))
	    return VALUES_1(ISVREF(curr,(SI_Long)3L));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REPRESENTATION-HANDLE-PUTHASH */
Object representation_handle_puthash(handle,representation)
    Object handle, representation;
{
    Object temp;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(92,58);
    gensymed_symbol = IFIX(handle);
    temp = The_representation_handle_hashtable;
    temp_1 = gensymed_symbol % (SI_Long)109L;
    return set_skip_list_entry(SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
	    Qeq,
	    Fp_mutate_representation_handle_tree_for_hash_skip_list_entry,
	    T,handle,FIX(gensymed_symbol),representation);
}

/* REPRESENTATION-HANDLE-REMHASH */
Object representation_handle_remhash(handle)
    Object handle;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash, old_entry;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(92,59);
    gensymed_symbol = IFIX(handle);
    temp = The_representation_handle_hashtable;
    temp_1 = gensymed_symbol % (SI_Long)109L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = handle;
    key_hash_value = gensymed_symbol;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
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
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? (EQ(key_value,
	    ISVREF(curr,(SI_Long)2L)) ? TRUEP(ISVREF(curr,(SI_Long)3L)) : 
	    TRUEP(Nil)) : TRUEP(Nil)) {
	gensymed_symbol = IFIX(handle);
	temp = The_representation_handle_hashtable;
	temp_1 = gensymed_symbol % (SI_Long)109L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),handle,
		SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
		FIX(gensymed_symbol));
	old_entry = NTH_VALUE((SI_Long)1L, result);
	if (old_entry)
	    IDENTITY(old_entry);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_callback_representation_subscription_handle, Qcurrent_callback_representation_subscription_handle);

/* NEW-CALLBACK-REPRESENTATION-SUBSCRIPTION-HANDLE */
Object new_callback_representation_subscription_handle()
{
    Object temp, current_callback_representation_subscription_handle_new_value;

    x_note_fn_call(92,60);
    temp = Current_callback_representation_subscription_handle;
    current_callback_representation_subscription_handle_new_value = 
	    FIXNUM_ADD1(Current_callback_representation_subscription_handle);
    Current_callback_representation_subscription_handle = 
	    current_callback_representation_subscription_handle_new_value;
    return VALUES_1(temp);
}

/* RECLAIM-CALLBACK-REPRESENTATION-CALLBACK-SERIAL-NUMBER-VALUE */
Object reclaim_callback_representation_callback_serial_number_value(serial_number,
	    callback_representation)
    Object serial_number, callback_representation;
{
    x_note_fn_call(92,61);
    reclaim_frame_serial_number(serial_number);
    ISVREF(callback_representation,(SI_Long)11L) = Nil;
    return VALUES_1(Nil);
}

/* ASSIGN-CALLBACK-REPRESENTATION-SUBSCRIPTION-HANDLE */
Object assign_callback_representation_subscription_handle(callback_representation)
    Object callback_representation;
{
    Object svref_new_value;

    x_note_fn_call(92,62);
    svref_new_value = new_callback_representation_subscription_handle();
    return VALUES_1(ISVREF(callback_representation,(SI_Long)12L) = 
	    svref_new_value);
}

/* STORE-CALLBACK-REPRESENTATION */
Object store_callback_representation(callback_representation)
    Object callback_representation;
{
    Object handle;

    x_note_fn_call(92,63);
    handle = ISVREF(callback_representation,(SI_Long)12L);
    if (handle);
    else
	handle = 
		assign_callback_representation_subscription_handle(callback_representation);
    representation_handle_puthash(handle,callback_representation);
    return VALUES_1(handle);
}

/* CALLBACK-REPRESENTATION-FIRE-CALLBACK */
Object callback_representation_fire_callback(representation,socket_1,
	    argument_list)
    Object representation, socket_1, argument_list;
{
    x_note_fn_call(92,64);
    if (EQ(socket_1,Local_pseudo_socket))
	start_local_representation_callback(representation,argument_list);
    else
	start_remote_representation_callback(socket_1,
		ISVREF(representation,(SI_Long)10L),argument_list);
    return VALUES_1(Nil);
}

/* RECLAIM-ITEM-REPRESENTATION-DENOTATION-VALUE */
Object reclaim_item_representation_denotation_value(denotation,frame)
    Object denotation, frame;
{
    x_note_fn_call(92,65);
    if (denotation) {
	reclaim_denotation_function(denotation);
	ISVREF(frame,(SI_Long)13L) = Nil;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-ITEM-REPRESENTATION-USER-DATA-VALUE-VALUE */
Object reclaim_item_representation_user_data_value_value(user_data,frame)
    Object user_data, frame;
{
    x_note_fn_call(92,66);
    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
	    SIMPLE_VECTOR_P(user_data)))
	reclaim_if_evaluation_value_1(user_data);
    ISVREF(frame,(SI_Long)14L) = Nil;
    return VALUES_1(Nil);
}

static Object Qitem_representation;  /* item-representation */

static Object Qws_representation;  /* ws-representation */

/* DELETE-REPRESENTATION */
Object delete_representation varargs_1(int, n)
{
    Object representation;
    Object remove_from_socket_p, represented_frame, icp_socket;
    Object svref_new_value, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(92,67);
    INIT_ARGS_nonrelocating();
    representation = REQUIRED_ARG_nonrelocating();
    remove_from_socket_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    represented_frame = ISVREF(representation,(SI_Long)9L);
    icp_socket = getf(ISVREF(representation,(SI_Long)8L),Qsocket,_);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(represented_frame,Qframe_representations);
    svref_new_value = delete_slot_value_element_1(representation,
	    ISVREF(represented_frame,(SI_Long)9L));
    SVREF(represented_frame,FIX((SI_Long)9L)) = svref_new_value;
    if (remove_from_socket_p &&  !EQ(icp_socket,Local_pseudo_socket)) {
	svref_new_value = delete_gensym_element_1(representation,
		ISVREF(icp_socket,(SI_Long)39L));
	SVREF(icp_socket,FIX((SI_Long)39L)) = svref_new_value;
    }
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
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
    if (temp ? TRUEP(ISVREF(representation,(SI_Long)15L)) : TRUEP(Nil))
	remove_subscription(ISVREF(representation,(SI_Long)15L),
		representation);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qws_representation,
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
    if (temp)
	cleanup_ws_representation(representation);
    representation_handle_remhash(ISVREF(representation,(SI_Long)12L));
    return delete_frame(representation);
}

/* DELETE-ALL-REPRESENTATIONS-FOR-ICP-SOCKET */
Object delete_all_representations_for_icp_socket(icp_socket)
    Object icp_socket;
{
    Object representations, representation, ab_loop_list_;

    x_note_fn_call(92,68);
    representations = copy_list_using_gensym_conses_1(ISVREF(icp_socket,
	    (SI_Long)39L));
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_representation(2,representation,Nil);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(representations);
    reclaim_gensym_list_1(ISVREF(icp_socket,(SI_Long)39L));
    SVREF(icp_socket,FIX((SI_Long)39L)) = Nil;
    return VALUES_1(Qnil);
}

/* GET-INTERFACE-FROM-REPRESENTATION */
Object get_interface_from_representation(representation)
    Object representation;
{
    Object socket_qm, temp;

    x_note_fn_call(92,69);
    socket_qm = getf(ISVREF(representation,(SI_Long)8L),Qsocket,_);
    temp = socket_qm ? ISVREF(socket_qm,(SI_Long)5L) : Qnil;
    return VALUES_1(temp);
}

/* SEND-REPRESENTATION-DELETION-NOTIFICATION */
Object send_representation_deletion_notification(representation)
    Object representation;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(92,70);
    gensymed_symbol = ISVREF(representation,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
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
	send_item_representation_deletion_notification(representation);
    return VALUES_1(Nil);
}

/* SEND-ITEM-REPRESENTATION-DELETION-NOTIFICATION */
Object send_item_representation_deletion_notification(representation)
    Object representation;
{
    Object denotation, gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object thing, argument_list, address, socket_1;

    x_note_fn_call(92,71);
    denotation = ISVREF(representation,(SI_Long)13L);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qdelete;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = denotation_gt_denotation_sequence(1,denotation);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    argument_list = gensymed_symbol;
    address = ISVREF(representation,(SI_Long)8L);
    socket_1 = getfq_function_no_default(address,Qsocket);
    callback_representation_fire_callback(representation,socket_1,
	    argument_list);
    return VALUES_1(Nil);
}

static Object Qitem_color_pattern_change;  /* item-color-pattern-change */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qab_structure;       /* structure */

/* SEND-ITEM-REPRESENTATION-ITEM-COLOR-PATTERN-CHANGE-NOTIFICATION */
Object send_item_representation_item_color_pattern_change_notification(representation,
	    color_or_pattern,specific_region_qm)
    Object representation, color_or_pattern, specific_region_qm;
{
    Object denotation, gensymed_symbol, gensymed_symbol_1, temp;
    Object gensymed_symbol_2, item_or_value, x2, svref_new_value, thing;
    Object argument_list, socket_1;
    SI_Long gensymed_symbol_3, svref_arg_2;
    char temp_1;

    x_note_fn_call(92,72);
    denotation = ISVREF(representation,(SI_Long)13L);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qitem_color_pattern_change;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = ISVREF(representation,(SI_Long)9L);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = denotation_gt_denotation_sequence(1,denotation);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    if (SYMBOLP(color_or_pattern)) {
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)2L + 
		(SI_Long)1L));
	gensymed_symbol_3 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_3 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_3 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_3 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = specific_region_qm;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = specific_region_qm;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = color_or_pattern;
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
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = color_or_pattern;
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
	temp = eval_cons_1(gensymed_symbol_2,Qab_structure);
    }
    else
	temp = export_color_pattern(color_or_pattern);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    temp = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = temp;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = temp;
    argument_list = gensymed_symbol;
    socket_1 = getfq_function_no_default(ISVREF(representation,
	    (SI_Long)8L),Qsocket);
    callback_representation_fire_callback(representation,socket_1,
	    argument_list);
    return VALUES_1(Nil);
}

static Object Qcustom_event;       /* custom-event */

/* SEND-ITEM-REPRESENTATION-CUSTOM-EVENT-NOTIFICATION */
Object send_item_representation_custom_event_notification(representation,
	    event_info)
    Object representation, event_info;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, car_new_value, thing;

    x_note_fn_call(92,73);
    temp = getfq_function_no_default(ISVREF(representation,(SI_Long)8L),
	    Qsocket);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qcustom_event;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)9L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = denotation_gt_denotation_sequence(1,
	    ISVREF(representation,(SI_Long)13L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = FIXNUMP(event_info) || event_info && 
	    SYMBOLP(event_info) || SIMPLE_VECTOR_P(event_info) ? 
	    event_info : copy_if_evaluation_value_1(event_info);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    callback_representation_fire_callback(representation,temp,gensymed_symbol);
    return VALUES_1(Nil);
}

/* SEND-ITEM-REPRESENTATION-ITEM-EVENT-NOTIFICATION */
Object send_item_representation_item_event_notification(representation)
    Object representation;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, car_new_value, thing;

    x_note_fn_call(92,74);
    temp = getfq_function_no_default(ISVREF(representation,(SI_Long)8L),
	    Qsocket);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qdelete;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = denotation_gt_denotation_sequence(1,
	    ISVREF(representation,(SI_Long)13L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Nil;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    callback_representation_fire_callback(representation,temp,gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qadd_item_to_workspace;  /* add-item-to-workspace */

/* SEND-ITEM-REPRESENTATION-ADD-ITEM-TO-WORKSPACE-NOTIFICATION */
Object send_item_representation_add_item_to_workspace_notification(representation,
	    item)
    Object representation, item;
{
    x_note_fn_call(92,75);
    send_item_representation_add_or_remove_item_from_workspace_notification(representation,
	    item,Qadd_item_to_workspace);
    return VALUES_1(Nil);
}

static Object Qremove_item_from_workspace;  /* remove-item-from-workspace */

/* SEND-ITEM-REPRESENTATION-REMOVE-ITEM-FROM-WORKSPACE-NOTIFICATION */
Object send_item_representation_remove_item_from_workspace_notification(representation,
	    item)
    Object representation, item;
{
    x_note_fn_call(92,76);
    send_item_representation_add_or_remove_item_from_workspace_notification(representation,
	    item,Qremove_item_from_workspace);
    return VALUES_1(Nil);
}

/* SEND-ITEM-REPRESENTATION-ADD-OR-REMOVE-ITEM-FROM-WORKSPACE-NOTIFICATION */
Object send_item_representation_add_or_remove_item_from_workspace_notification(representation,
	    item,event_name)
    Object representation, item, event_name;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, car_new_value, thing;

    x_note_fn_call(92,77);
    temp = getfq_function_no_default(ISVREF(representation,(SI_Long)8L),
	    Qsocket);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = event_name;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)9L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = denotation_gt_denotation_sequence(1,
	    ISVREF(representation,(SI_Long)13L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = item;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    callback_representation_fire_callback(representation,temp,gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qmodify;             /* modify */

/* UPDATE-REPRESENTED-ITEM-DENOTATION-VALUE */
Object update_represented_item_denotation_value(representation,frame,
	    denotation)
    Object representation, frame, denotation;
{
    Object attribute_evaluation_value, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, thing, argument_list, address, socket_1;

    x_note_fn_call(92,78);
    attribute_evaluation_value = get_denoted_evaluation_value(frame,
	    denotation);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qmodify;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = frame;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = denotation_gt_denotation_sequence(1,denotation);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = attribute_evaluation_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(representation,(SI_Long)12L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    argument_list = gensymed_symbol;
    address = ISVREF(representation,(SI_Long)8L);
    socket_1 = getfq_function_no_default(address,Qsocket);
    callback_representation_fire_callback(representation,socket_1,
	    argument_list);
    return VALUES_1(Nil);
}

static Object Qhandle;             /* handle */

static Object Qby_copy_with_handle;  /* by-copy-with-handle */

static Object Qcopy;               /* copy */

static Object Qvalue;              /* value */

/* TRANSFORM-SYSTEM-RPC-ARGUMENTS */
Object transform_system_rpc_arguments(icp_socket,argument_list,info_list,
	    remote_representation_callback_p,varargs_p)
    Object icp_socket, argument_list, info_list;
    Object remote_representation_callback_p, varargs_p;
{
    Object current_computation_flags, info_list_tail, kind, argument_tail;
    Object argument, ab_loop_iter_flag_, x2, temp_1, temp_2, car_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(92,79);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      info_list_tail = info_list;
      kind = Nil;
      argument_tail = argument_list;
      argument = Nil;
      ab_loop_iter_flag_ = T;
      if (ISVREF(icp_socket,(SI_Long)48L))
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)16L);
      else
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  &  ~(SI_Long)16L);
    next_loop:
      kind = remote_representation_callback_p ? Qhandle : 
	      remote_procedure_item_info_kind_function(CAR(info_list_tail));
      if ( !TRUEP(ab_loop_iter_flag_))
	  argument_tail = M_CDR(argument_tail);
      if ( !TRUEP(argument_tail))
	  goto end_loop;
      argument = CAR(argument_tail);
      if (SIMPLE_VECTOR_P(argument) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument)) > (SI_Long)2L &&  
	      !EQ(ISVREF(argument,(SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(argument,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  if (EQ(kind,Qby_copy_with_handle)) {
	      temp_1 = argument;
	      temp_2 = make_remote_procedure_item_info(Nil,Nil,Nil,Nil,Nil,
		      kind);
	      car_new_value = icp_list_4(Qcopy,temp_1,temp_2,
		      ensure_registration_on_network(argument,
		      ISVREF(icp_socket,(SI_Long)5L)));
	  }
	  else if (EQ(kind,Qhandle)) {
	      ensure_registration_on_network(argument,ISVREF(icp_socket,
		      (SI_Long)5L));
	      car_new_value = icp_cons_1(Qhandle,argument);
	  }
	  else {
	      temp_2 = argument;
	      car_new_value = icp_list_3(Qcopy,temp_2,
		      make_remote_procedure_item_info(Nil,Nil,Nil,Nil,Nil,
		      kind));
	  }
      }
      else if (EQ(kind,Qhandle)) {
	  register_all_items_in_value(argument,ISVREF(icp_socket,(SI_Long)5L));
	  car_new_value = icp_cons_1(Qhandle,argument);
      }
      else
	  car_new_value = icp_cons_1(Qvalue,argument);
      M_CAR(argument_tail) = car_new_value;
      ab_loop_iter_flag_ = Nil;
      info_list_tail =  !TRUEP(CDR(info_list_tail)) && varargs_p ? 
	      info_list_tail : CDR(info_list_tail);
      goto next_loop;
    end_loop:
      temp_2 = Qnil;
    POP_SPECIAL();
    return VALUES_1(temp_2);
}

/* START-REMOTE-REPRESENTATION-CALLBACK */
Object start_remote_representation_callback(icp_socket,callback_procedure,
	    argument_list)
    Object icp_socket, callback_procedure, argument_list;
{
    x_note_fn_call(92,80);
    if (SYMBOLP(callback_procedure))
	return FUNCALL_1(callback_procedure,argument_list);
    else if ( !TRUEP(icp_connection_open_p(icp_socket)) || 
	    icp_connection_being_shutdown_qm(icp_socket))
	return reclaim_rpc_argument_list(argument_list,Nil);
    else {
	transform_system_rpc_arguments(icp_socket,argument_list,Nil,T,Nil);
	return send_rpc_start(ISVREF(icp_socket,(SI_Long)4L),
		FIX((SI_Long)6L),callback_procedure,argument_list,Nil);
    }
}

/* UPDATE-SUBSCRIPTIONS-FROM-VIRTUAL-ATTRIBUTE-CHANGE */
Object update_subscriptions_from_virtual_attribute_change(frame,
	    virtual_attribute,defining_class_qm)
    Object frame, virtual_attribute, defining_class_qm;
{
    Object gensymed_symbol, list_1, subscriptions, attribute_name;

    x_note_fn_call(92,81);
    gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    attribute_name = ISVREF(virtual_attribute,(SI_Long)1L);
    if (subscriptions)
	update_subscriptions(frame,
		make_virtual_attribute_denotation(virtual_attribute,Nil),
		subscriptions);
    chain_forward_for_attribute_if_necessary(frame,attribute_name,
	    defining_class_qm);
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FROM-VARIABLE-CHANGE */
Object update_subscriptions_from_variable_change(frame)
    Object frame;
{
    Object gensymed_symbol, list_1, subscriptions;

    x_note_fn_call(92,82);
    gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions)
	update_subscriptions(frame,make_variable_value_denotation(Nil),
		subscriptions);
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FROM-SLOT-CHANGE */
Object update_subscriptions_from_slot_change(frame,slot_description,
	    slot_name,defining_class_qm)
    Object frame, slot_description, slot_name, defining_class_qm;
{
    Object gensymed_symbol, list_1, subscriptions, temp, defining_class;
    Object temp_1, attribute_name;

    x_note_fn_call(92,83);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
		Current_kb_specific_property_list_property_name))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:
	list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
      next_loop_1:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	    goto end_loop_1;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop_1;
      end_loop_1:
	subscriptions = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
	if (subscriptions) {
	    temp = ISVREF(slot_description,(SI_Long)2L);
	    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		defining_class = ISVREF(slot_description,(SI_Long)3L);
		temp_1 =  !EQ(defining_class,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			(SI_Long)2L),ISVREF(frame,(SI_Long)1L),Nil),
			(SI_Long)3L)) ? defining_class : Nil;
	    }
	    else
		temp_1 = Nil;
	    update_subscriptions(frame,make_attribute_denotation(temp,
		    temp_1,Nil),subscriptions);
	}
    }
    else {
	temp = ISVREF(slot_description,(SI_Long)10L);
	if (temp);
	else
	    temp = cache_evaluator_slot_info(slot_description);
	if (ISVREF(temp,(SI_Long)3L)) {
	    subscriptions = 
		    lookup_kb_specific_property_value(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)1L),Class_subscriptions_kbprop);
	    slot_name = ISVREF(slot_description,(SI_Long)2L);
	    attribute_name = get_alias_for_slot_name_if_any(slot_name,frame);
	    if (attribute_name);
	    else
		attribute_name = slot_name;
	    defining_class_qm = Nil;
	    if (subscriptions)
		update_subscriptions(frame,
			make_attribute_denotation(attribute_name,
			defining_class_qm,Nil),subscriptions);
	    chain_forward_for_attribute_if_necessary(frame,attribute_name,
		    defining_class_qm);
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-REPRESENTATION-DISPATCH */
Object update_representation_dispatch(representation,frame,
	    attribute_description)
    Object representation, frame, attribute_description;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(92,84);
    gensymed_symbol = ISVREF(representation,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
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
	return VALUES_1(attribute_description);
    else
	return VALUES_1(Nil);
}

/* UPDATE-REPRESENTATION-WITH-DENOTATION */
Object update_representation_with_denotation(representation,frame,denotation)
    Object representation, frame, denotation;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(92,85);
    gensymed_symbol = ISVREF(representation,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qitem_representation,
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
	return update_represented_item_denotation_value(representation,
		frame,denotation);
    else
	return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS */
Object update_subscriptions(frame,denotation,subscriptions)
    Object frame, denotation, subscriptions;
{
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, gensymed_symbol, xa, ya;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,86);
    matching_subscriptions = match_subscriptions(subscriptions,denotation,
	    FIX((SI_Long)0L));
    if (matching_subscriptions) {
	cache = make_item_access_cache();
	representations = gather_affected_representations(cache,
		matching_subscriptions,frame);
	if (representations) {
	    reference = copy_frame_serial_number(Current_frame_serial_number);
	    representation = Nil;
	    ab_loop_list_ = representations;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    representation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(representation) ? 
		    EQ(ISVREF(representation,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(reference))
		temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(reference);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(reference),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if (temp);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(Qitem_representation,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(representation,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if ( !temp)
		update_represented_item_denotation_value(representation,
			ISVREF(representation,(SI_Long)9L),denotation);
	    goto next_loop;
	  end_loop:
	    reclaim_frame_serial_number(reference);
	    reclaim_gensym_list_1(representations);
	}
	delete_item_access_cache(cache);
	reclaim_gensym_list_1(matching_subscriptions);
    }
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FOR-COLOR-CHANGE */
Object update_subscriptions_for_color_change(frame,color_or_pattern,region_qm)
    Object frame, color_or_pattern, region_qm;
{
    Object gensymed_symbol, list_1, subscriptions_qm, denotation;
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, xa, ya, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,87);
    gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions_qm) {
	denotation = make_item_color_pattern_change_denotation();
	matching_subscriptions = match_subscriptions(subscriptions_qm,
		denotation,FIX((SI_Long)0L));
	if (matching_subscriptions) {
	    cache = make_item_access_cache();
	    representations = gather_affected_representations(cache,
		    matching_subscriptions,frame);
	    if (representations) {
		reference = 
			copy_frame_serial_number(Current_frame_serial_number);
		representation = Nil;
		ab_loop_list_ = representations;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		representation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation) ? 
			EQ(ISVREF(representation,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference))
		    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			    gensymed_symbol) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(reference);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(reference),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qitem_representation,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(representation,(SI_Long)1L),
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		if ( !temp)
		    send_item_representation_item_color_pattern_change_notification(representation,
			    color_or_pattern,region_qm);
		goto next_loop_2;
	      end_loop_2:
		reclaim_frame_serial_number(reference);
		reclaim_gensym_list_1(representations);
	    }
	    delete_item_access_cache(cache);
	    reclaim_gensym_list_1(matching_subscriptions);
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FOR-CUSTOM-EVENT */
Object update_subscriptions_for_custom_event(frame,event_name,event_info)
    Object frame, event_name, event_info;
{
    Object gensymed_symbol, list_1, subscriptions_qm, denotation;
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, xa, ya, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,88);
    gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions_qm) {
	denotation = make_custom_event_denotation(event_name);
	matching_subscriptions = match_subscriptions(subscriptions_qm,
		denotation,FIX((SI_Long)0L));
	if (matching_subscriptions) {
	    cache = make_item_access_cache();
	    representations = gather_affected_representations(cache,
		    matching_subscriptions,frame);
	    if (representations) {
		reference = 
			copy_frame_serial_number(Current_frame_serial_number);
		representation = Nil;
		ab_loop_list_ = representations;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		representation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation) ? 
			EQ(ISVREF(representation,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference))
		    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			    gensymed_symbol) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(reference);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(reference),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qitem_representation,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(representation,(SI_Long)1L),
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		if ( !temp)
		    send_item_representation_custom_event_notification(representation,
			    event_info);
		goto next_loop_2;
	      end_loop_2:
		reclaim_frame_serial_number(reference);
		reclaim_gensym_list_1(representations);
	    }
	    delete_item_access_cache(cache);
	    reclaim_gensym_list_1(matching_subscriptions);
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FOR-ITEM-EVENT */
Object update_subscriptions_for_item_event(frame,event_name)
    Object frame, event_name;
{
    Object gensymed_symbol, list_1, subscriptions_qm, denotation;
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, xa, ya, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,89);
    gensymed_symbol = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions_qm) {
	denotation = make_item_event_denotation(event_name);
	matching_subscriptions = match_subscriptions(subscriptions_qm,
		denotation,FIX((SI_Long)0L));
	if (matching_subscriptions) {
	    cache = make_item_access_cache();
	    representations = gather_affected_representations(cache,
		    matching_subscriptions,frame);
	    if (representations) {
		reference = 
			copy_frame_serial_number(Current_frame_serial_number);
		representation = Nil;
		ab_loop_list_ = representations;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		representation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation) ? 
			EQ(ISVREF(representation,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference))
		    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			    gensymed_symbol) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(reference);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(reference),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qitem_representation,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(representation,(SI_Long)1L),
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		if ( !temp)
		    send_item_representation_item_event_notification(representation);
		goto next_loop_2;
	      end_loop_2:
		reclaim_frame_serial_number(reference);
		reclaim_gensym_list_1(representations);
	    }
	    delete_item_access_cache(cache);
	    reclaim_gensym_list_1(matching_subscriptions);
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FOR-ADD-ITEM-TO-WORKSPACE */
Object update_subscriptions_for_add_item_to_workspace(ws,item)
    Object ws, item;
{
    Object gensymed_symbol, list_1, subscriptions_qm, denotation;
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, xa, ya, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,90);
    gensymed_symbol = ISVREF(ISVREF(ws,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions_qm) {
	denotation = make_add_item_to_workspace_denotation();
	matching_subscriptions = match_subscriptions(subscriptions_qm,
		denotation,FIX((SI_Long)0L));
	if (matching_subscriptions) {
	    cache = make_item_access_cache();
	    representations = gather_affected_representations(cache,
		    matching_subscriptions,ws);
	    if (representations) {
		reference = 
			copy_frame_serial_number(Current_frame_serial_number);
		representation = Nil;
		ab_loop_list_ = representations;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		representation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation) ? 
			EQ(ISVREF(representation,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference))
		    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			    gensymed_symbol) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(reference);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(reference),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qitem_representation,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(representation,(SI_Long)1L),
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		if ( !temp)
		    send_item_representation_add_or_remove_item_from_workspace_notification(representation,
			    item,Qadd_item_to_workspace);
		goto next_loop_2;
	      end_loop_2:
		reclaim_frame_serial_number(reference);
		reclaim_gensym_list_1(representations);
	    }
	    delete_item_access_cache(cache);
	    reclaim_gensym_list_1(matching_subscriptions);
	}
    }
    return VALUES_1(Nil);
}

/* UPDATE-SUBSCRIPTIONS-FOR-REMOVE-ITEM-FROM-WORKSPACE */
Object update_subscriptions_for_remove_item_from_workspace(ws,item)
    Object ws, item;
{
    Object gensymed_symbol, list_1, subscriptions_qm, denotation;
    Object matching_subscriptions, cache, representations, reference;
    Object representation, ab_loop_list_, xa, ya, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(92,91);
    gensymed_symbol = ISVREF(ISVREF(ws,(SI_Long)1L),(SI_Long)1L);
    list_1 = INLINE_SYMBOL_PLIST(gensymed_symbol);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Class_subscriptions_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    subscriptions_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (subscriptions_qm) {
	denotation = make_remove_item_from_workspace_denotation();
	matching_subscriptions = match_subscriptions(subscriptions_qm,
		denotation,FIX((SI_Long)0L));
	if (matching_subscriptions) {
	    cache = make_item_access_cache();
	    representations = gather_affected_representations(cache,
		    matching_subscriptions,ws);
	    if (representations) {
		reference = 
			copy_frame_serial_number(Current_frame_serial_number);
		representation = Nil;
		ab_loop_list_ = representations;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		representation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation) ? 
			EQ(ISVREF(representation,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(reference))
		    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference,
			    gensymed_symbol) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(reference);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(reference),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if (temp);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qitem_representation,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(representation,(SI_Long)1L),
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		}
		if ( !temp)
		    send_item_representation_add_or_remove_item_from_workspace_notification(representation,
			    item,Qremove_item_from_workspace);
		goto next_loop_2;
	      end_loop_2:
		reclaim_frame_serial_number(reference);
		reclaim_gensym_list_1(representations);
	    }
	    delete_item_access_cache(cache);
	    reclaim_gensym_list_1(matching_subscriptions);
	}
    }
    return VALUES_1(Nil);
}

Object The_type_description_of_deferred_update = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_deferred_updates, Qchain_of_available_deferred_updates);

DEFINE_VARIABLE_WITH_SYMBOL(Deferred_update_count, Qdeferred_update_count);

Object Chain_of_available_deferred_updates_vector = UNBOUND;

/* DEFERRED-UPDATE-STRUCTURE-MEMORY-USAGE */
Object deferred_update_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(92,92);
    temp = Deferred_update_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DEFERRED-UPDATE-COUNT */
Object outstanding_deferred_update_count()
{
    Object def_structure_deferred_update_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(92,93);
    gensymed_symbol = IFIX(Deferred_update_count);
    def_structure_deferred_update_variable = 
	    Chain_of_available_deferred_updates;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_deferred_update_variable))
	goto end_loop;
    def_structure_deferred_update_variable = 
	    ISVREF(def_structure_deferred_update_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DEFERRED-UPDATE-1 */
Object reclaim_deferred_update_1(deferred_update)
    Object deferred_update;
{
    Object temp, svref_arg_2;

    x_note_fn_call(92,94);
    inline_note_reclaim_cons(deferred_update,Nil);
    temp = ISVREF(Chain_of_available_deferred_updates_vector,
	    IFIX(Current_thread_index));
    SVREF(deferred_update,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_deferred_updates_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = deferred_update;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DEFERRED-UPDATE */
Object reclaim_structure_for_deferred_update(deferred_update)
    Object deferred_update;
{
    x_note_fn_call(92,95);
    return reclaim_deferred_update_1(deferred_update);
}

static Object Qg2_defstruct_structure_name_deferred_update_g2_struct;  /* g2-defstruct-structure-name::deferred-update-g2-struct */

/* MAKE-PERMANENT-DEFERRED-UPDATE-STRUCTURE-INTERNAL */
Object make_permanent_deferred_update_structure_internal()
{
    Object def_structure_deferred_update_variable;
    Object defstruct_g2_deferred_update_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(92,96);
    def_structure_deferred_update_variable = Nil;
    atomic_incff_symval(Qdeferred_update_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_deferred_update_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_deferred_update_variable = the_array;
	SVREF(defstruct_g2_deferred_update_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_deferred_update_g2_struct;
	def_structure_deferred_update_variable = 
		defstruct_g2_deferred_update_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_deferred_update_variable);
}

/* MAKE-DEFERRED-UPDATE-1 */
Object make_deferred_update_1()
{
    Object def_structure_deferred_update_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(92,97);
    def_structure_deferred_update_variable = 
	    ISVREF(Chain_of_available_deferred_updates_vector,
	    IFIX(Current_thread_index));
    if (def_structure_deferred_update_variable) {
	svref_arg_1 = Chain_of_available_deferred_updates_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_deferred_update_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_deferred_update_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_deferred_update_g2_struct;
    }
    else
	def_structure_deferred_update_variable = 
		make_permanent_deferred_update_structure_internal();
    inline_note_allocate_cons(def_structure_deferred_update_variable,Nil);
    SVREF(def_structure_deferred_update_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_deferred_update_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_deferred_update_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_deferred_update_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_deferred_update_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_deferred_update_variable);
}

/* CLEANUP-WS-REPRESENTATION */
Object cleanup_ws_representation(ws_representation)
    Object ws_representation;
{
    Object workspace;

    x_note_fn_call(92,98);
    workspace = ISVREF(ws_representation,(SI_Long)9L);
    if ( !(ISVREF(workspace,(SI_Long)16L) ||  !TRUEP(Nil) && 
	    workspace_showing_on_ui_client_p(workspace)))
	return event_update_status_of_block_showing(workspace,Nil,Nil);
    else
	return VALUES_1(Nil);
}

/* WS-HAS-WS-REPRESENTATION-P */
Object ws_has_ws_representation_p(frame)
    Object frame;
{
    Object representation, ab_loop_list_, ab_loop_it_, gensymed_symbol;
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(92,99);
    if (G2_has_v5_mode_windows_p) {
	representation = Nil;
	ab_loop_list_ = ISVREF(frame,(SI_Long)9L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	representation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qws_representation,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(representation,
		    (SI_Long)1L),(SI_Long)19L);
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
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
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

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

/* MAKE-STRUCTURE-FROM-DIMENSIONS */
Object make_structure_from_dimensions(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(92,100);
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
	item_or_value = left;
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
	item_or_value = left;
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
	item_or_value = top;
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
	item_or_value = top;
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
	item_or_value = right;
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
	item_or_value = right;
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
	item_or_value = bottom;
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
	item_or_value = bottom;
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

static Object Qworkspace_dimensions;  /* workspace-dimensions */

static Object Qworkspace_background_color;  /* workspace-background-color */

static Object Qworkspace_foreground_color;  /* workspace-foreground-color */

static Object Qitem_info_list;     /* item-info-list */

static Object Qitem_data_list;     /* item-data-list */

/* CREATE-WS-REPRESENTATION-UPDATED-STATE */
Object create_ws_representation_updated_state(ws,slots_to_update)
    Object ws, slots_to_update;
{
    Object gensymed_symbol, subblocks, queue, next_queue_element, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, subblocks_1, items, first_item, temp;
    Object temp_1, temp_2, workspace_dimensions, workspace_background_color;
    Object workspace_foreground_color, first_item_info, item_info_list;
    Object items_to_export, item_datas_to_export, item1, item2, ab_loop_list_;
    Object item_data, item, temp_3, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_4;

    x_note_fn_call(92,101);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    if (subblocks) {
	queue = subblocks;
	next_queue_element = Nil;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),
		queue);
      next_loop:
	if ( !TRUEP(next_queue_element))
	    goto end_loop;
	gensymed_symbol = ISVREF(next_queue_element,(SI_Long)4L);
	next_queue_element = constant_queue_next(next_queue_element,queue);
	ab_loopvar__2 = slot_value_cons_1(gensymed_symbol,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	subblocks_1 = ab_loopvar_;
	goto end_1;
	subblocks_1 = Qnil;
      end_1:;
    }
    else
	subblocks_1 = Nil;
    items = reverse_item_like_children(subblocks_1);
    first_item = CAR(items);
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    workspace_dimensions = make_structure_from_dimensions(temp,temp_1,
	    temp_2,gensymed_symbol);
    workspace_background_color = ISVREF(ws,(SI_Long)21L);
    workspace_foreground_color = ISVREF(ws,(SI_Long)22L);
    first_item_info = first_item ? 
	    get_thing_updated_info_with_all_children(first_item,Nil,
	    slots_to_update) : Nil;
    item_info_list = first_item_info;
    items_to_export = Nil;
    item_datas_to_export = Nil;
    item1 = Nil;
    item2 = Nil;
    ab_loop_list_ = items;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    item1 = CAR(ab_loop_list_);
    temp_2 = CDR(ab_loop_list_);
    item2 = CAR(temp_2);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (item2) {
	temp_2 = get_thing_updated_info_with_all_children(item2,Nil,
		slots_to_update);
	item_info_list = nconc2(temp_2,item_info_list);
    }
    goto next_loop_1;
  end_loop_1:
    item_data = Nil;
    item = Nil;
    ab_loop_list_ = item_info_list;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
  next_loop_2:
    item_data = CAR(ab_loop_list_);
    temp_2 = CDR(ab_loop_list_);
    item = CAR(temp_2);
    item_datas_to_export = eval_cons_1(item_data,item_datas_to_export);
    items_to_export = eval_cons_1(item,items_to_export);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    reclaim_gensym_list_1(item_info_list);
    reclaim_gensym_list_1(items);
    reclaim_slot_value_list_1(subblocks_1);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
	    (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_3,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qworkspace_dimensions;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)1L)) = Qworkspace_dimensions;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_dimensions;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_dimensions;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qworkspace_background_color;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)3L)) = Qworkspace_background_color;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_background_color;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_background_color;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qworkspace_foreground_color;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)5L)) = Qworkspace_foreground_color;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_foreground_color;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_foreground_color;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qitem_info_list;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)7L)) = Qitem_info_list;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(items_to_export);
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(items_to_export);
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qitem_data_list;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)9L)) = Qitem_data_list;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(item_datas_to_export);
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(item_datas_to_export);
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)10L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(Qnil);
}

/* CREATE-WS-REPRESENTATION-INITIAL-STATE */
Object create_ws_representation_initial_state(ws)
    Object ws;
{
    Object gensymed_symbol, subblocks, queue, next_queue_element, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, subblocks_1, items, first_item, temp;
    Object temp_1, temp_2, workspace_dimensions, workspace_background_color;
    Object workspace_foreground_color, first_item_info, item_info_list;
    Object items_to_export, item_datas_to_export, item1, item2, ab_loop_list_;
    Object item_data, item, temp_3, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_4;

    x_note_fn_call(92,102);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    subblocks = gensymed_symbol;
    if (subblocks) {
	queue = subblocks;
	next_queue_element = Nil;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),
		queue);
      next_loop:
	if ( !TRUEP(next_queue_element))
	    goto end_loop;
	gensymed_symbol = ISVREF(next_queue_element,(SI_Long)4L);
	next_queue_element = constant_queue_next(next_queue_element,queue);
	ab_loopvar__2 = slot_value_cons_1(gensymed_symbol,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	subblocks_1 = ab_loopvar_;
	goto end_1;
	subblocks_1 = Qnil;
      end_1:;
    }
    else
	subblocks_1 = Nil;
    items = nreverse(copy_list_using_gensym_conses_1(subblocks_1));
    first_item = CAR(items);
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(ws,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    workspace_dimensions = make_structure_from_dimensions(temp,temp_1,
	    temp_2,gensymed_symbol);
    workspace_background_color = ISVREF(ws,(SI_Long)21L);
    workspace_foreground_color = ISVREF(ws,(SI_Long)22L);
    first_item_info = first_item ? 
	    get_thing_initial_info_with_all_children(first_item,Nil) : Nil;
    item_info_list = first_item_info;
    items_to_export = Nil;
    item_datas_to_export = Nil;
    item1 = Nil;
    item2 = Nil;
    ab_loop_list_ = items;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    item1 = CAR(ab_loop_list_);
    temp_2 = CDR(ab_loop_list_);
    item2 = CAR(temp_2);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (item2) {
	temp_2 = get_thing_initial_info_with_all_children(item2,Nil);
	item_info_list = nconc2(temp_2,item_info_list);
    }
    goto next_loop_1;
  end_loop_1:
    item_data = Nil;
    item = Nil;
    ab_loop_list_ = item_info_list;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
  next_loop_2:
    item_data = CAR(ab_loop_list_);
    temp_2 = CDR(ab_loop_list_);
    item = CAR(temp_2);
    item_datas_to_export = eval_cons_1(item_data,item_datas_to_export);
    items_to_export = eval_cons_1(item,items_to_export);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    reclaim_gensym_list_1(item_info_list);
    reclaim_gensym_list_1(items);
    reclaim_slot_value_list_1(subblocks_1);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
	    (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_3,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qworkspace_dimensions;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)1L)) = Qworkspace_dimensions;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_dimensions;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_dimensions;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qworkspace_background_color;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)3L)) = Qworkspace_background_color;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_background_color;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_background_color;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qworkspace_foreground_color;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)5L)) = Qworkspace_foreground_color;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = workspace_foreground_color;
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = workspace_foreground_color;
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qitem_info_list;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)7L)) = Qitem_info_list;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(items_to_export);
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(items_to_export);
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qitem_data_list;
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_3,FIX((SI_Long)9L)) = Qitem_data_list;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(item_datas_to_export);
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
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_3;
    }
    else {
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(item_datas_to_export);
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
	svref_new_value = temp_4 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_3,FIX((SI_Long)10L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(Qnil);
}

/* GET-FIRST-ITEM-LIKE-CHILD */
Object get_first_item_like_child(block)
    Object block;
{
    Object children, child, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(92,103);
    children = nreverse(children_of_thing(2,block,T));
    child = Nil;
    ab_loop_list_ = children;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = v5_tw_item_like_p(child) &&  
	    !TRUEP(item_or_connection_being_deleted_p(child)) ? child : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(children);
    return VALUES_1(Qnil);
}

/* GET-TOPMOST-CHILD-OF-BLOCK */
Object get_topmost_child_of_block(block)
    Object block;
{
    Object topmost_child;

    x_note_fn_call(92,104);
    if (block) {
	topmost_child = get_first_item_like_child(block);
	if (topmost_child)
	    return get_topmost_child_of_block(topmost_child);
	else
	    return VALUES_1(block);
    }
    else
	return VALUES_1(Nil);
}

/* V5-TW-ITEM-LIKE-P */
Object v5_tw_item_like_p(block_or_connection)
    Object block_or_connection;
{
    Object x2, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(92,105);
    if (SIMPLE_VECTOR_P(block_or_connection) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(block_or_connection,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block_or_connection,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(block_or_connection,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Bounding_box_class_description,(SI_Long)18L));
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
	if ( !temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(block_or_connection,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Non_kb_workspace_class_description,
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(ISVREF(ISVREF(block_or_connection,(SI_Long)1L),
		    (SI_Long)16L));
	else
	    return VALUES_1(Nil);
    }
    else {
	temp_1 = SIMPLE_VECTOR_P(block_or_connection) ? 
		(EQ(ISVREF(block_or_connection,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct) ? T : 
		Nil) : Qnil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else
	    return VALUES_1(Nil);
    }
}

/* REVERSE-ITEM-LIKE-CHILDREN */
Object reverse_item_like_children(children)
    Object children;
{
    Object result_1, child, ab_loop_list_;

    x_note_fn_call(92,106);
    result_1 = Qnil;
    child = Nil;
    ab_loop_list_ = children;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (v5_tw_item_like_p(child))
	result_1 = gensym_cons_1(child,result_1);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* ITEM-LIKE-CHILDREN */
Object item_like_children(children)
    Object children;
{
    x_note_fn_call(92,107);
    return nreverse(reverse_item_like_children(children));
}

/* INPUT-END-CONNECTIONS-AND-OUTPUT-STUBS */
Object input_end_connections_and_output_stubs(item,exclude_output_stubs_p)
    Object item, exclude_output_stubs_p;
{
    Object result_1, connections, connection, ab_loop_list_;
    Object connection_frame_1;

    x_note_fn_call(92,108);
    result_1 = Nil;
    connections = connection_structures(item);
    connection = Nil;
    ab_loop_list_ = connections;
    connection_frame_1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    connection_frame_1 = 
	    get_or_make_connection_frame_and_activate_if_appropriate(connection);
    if (output_connection_p_function(item,connection) ||  
	    !TRUEP(exclude_output_stubs_p) && 
	    loose_end_connection_frame_p(connection_frame_1))
	result_1 = gensym_cons_1(connection_frame_1,result_1);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(connections);
    return nreverse(result_1);
    return VALUES_1(Qnil);
}

/* CHILDREN-OF-THING */
Object children_of_thing varargs_1(int, n)
{
    Object thing;
    Object exclude_output_stubs, x2, connections, gensymed_symbol, subblocks;
    Object queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, subblocks_1, all_subblocks;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(92,109);
    INIT_ARGS_nonrelocating();
    thing = REQUIRED_ARG_nonrelocating();
    exclude_output_stubs = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	connections = input_end_connections_and_output_stubs(thing,
		exclude_output_stubs);
	gensymed_symbol = ACCESS_ONCE(ISVREF(thing,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	if (subblocks) {
	    queue = subblocks;
	    next_queue_element = Nil;
	    gensymed_symbol = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    next_queue_element = constant_queue_next(ISVREF(queue,
		    (SI_Long)2L),queue);
	  next_loop:
	    if ( !TRUEP(next_queue_element))
		goto end_loop;
	    gensymed_symbol = ISVREF(next_queue_element,(SI_Long)4L);
	    next_queue_element = constant_queue_next(next_queue_element,queue);
	    ab_loopvar__2 = gensym_cons_1(gensymed_symbol,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    subblocks_1 = ab_loopvar_;
	    goto end_1;
	    subblocks_1 = Qnil;
	  end_1:;
	}
	else
	    subblocks_1 = Nil;
	all_subblocks = nconc2(subblocks_1,connections);
	return VALUES_1(all_subblocks);
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* GET-THING-UPDATED-INFO */
Object get_thing_updated_info(thing,slots_to_update)
    Object thing, slots_to_update;
{
    Object x2, sub_class_bit_vector, gensymed_symbol_3, svref_arg_1, structure;
    Object slot, ab_loop_list_, attribute_description_qm, val;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;

    x_note_fn_call(92,110);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	thing = 
		get_or_make_connection_frame_and_activate_if_appropriate(thing);
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
    if ( !temp) {
	gensymed_symbol_3 = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_3,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_3,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_3,(gensymed_symbol >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	structure = eval_cons_1(gensymed_symbol_3,Qab_structure);
	slot = Nil;
	ab_loop_list_ = slots_to_update;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	slot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),slot,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,slot,val);
	goto next_loop;
      end_loop:;
	return VALUES_1(structure);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrepresentation_type;  /* representation-type */

static Object Qitem_color_pattern;  /* item-color-pattern */

static Object Qconnection_style;   /* connection-style */

static Object Qconnection_is_directed;  /* connection-is-directed */

static Object Qconnection_position_sequence;  /* connection-position-sequence */

static Object Qrepresented_item;   /* represented-item */

static Object Qformat_type;        /* format-type */

static Object Qtable_rows;         /* table-rows */

static Object Qtable_cells;        /* table-cells */

static Object Qdefault_cell_format;  /* default-cell-format */

static Object Qtable_font_size;    /* table-font-size */

static Object Qitem_configuration;  /* item-configuration */

static Object Qmanually_disabled_qm;  /* manually-disabled? */

static Object Qtext_x_magnification;  /* text-x-magnification */

static Object Qtext_y_magnification;  /* text-y-magnification */

static Object Qitem_x_position;    /* item-x-position */

static Object Qitem_y_position;    /* item-y-position */

static Object Qitem_width;         /* item-width */

static Object Qitem_height;        /* item-height */

static Object Qicon_heading;       /* icon-heading */

static Object Qicon_reflection;    /* icon-reflection */

static Object Qicon_variables;     /* icon-variables */

/* GET-THING-INITIAL-INFO */
Object get_thing_initial_info(thing)
    Object thing;
{
    Object x2, sub_class_bit_vector, gensymed_symbol_3, svref_arg_1, structure;
    Object attribute_description_qm, val;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;

    x_note_fn_call(92,111);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	thing = 
		get_or_make_connection_frame_and_activate_if_appropriate(thing);
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
    if ( !temp) {
	gensymed_symbol_3 = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_3,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_3,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_3,(gensymed_symbol >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	structure = eval_cons_1(gensymed_symbol_3,Qab_structure);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qrepresentation_type,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qrepresentation_type,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qitem_color_pattern,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qitem_color_pattern,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qconnection_style,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qconnection_style,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qconnection_is_directed,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,
		    Qconnection_is_directed,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qconnection_position_sequence,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,
		    Qconnection_position_sequence,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qrepresented_item,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qrepresented_item,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qformat_type,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qformat_type,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qtable_rows,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qtable_rows,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qtable_cells,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qtable_cells,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qdefault_cell_format,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qdefault_cell_format,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qtable_font_size,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qtable_font_size,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qitem_configuration,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qitem_configuration,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qmanually_disabled_qm,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qmanually_disabled_qm,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qtext_x_magnification,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qtext_x_magnification,val);
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qtext_y_magnification,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qtext_y_magnification,val);
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
	if ( !temp) {
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qitem_x_position,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qitem_x_position,val);
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qitem_y_position,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qitem_y_position,val);
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qitem_width,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qitem_width,val);
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qitem_height,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qitem_height,val);
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qicon_heading,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qicon_heading,val);
	    attribute_description_qm = 
		    get_attribute_description_from_class_description(ISVREF(thing,
		    (SI_Long)1L),Qicon_reflection,Nil);
	    val = attribute_description_qm ? 
		    get_attribute_description_evaluation_value(thing,
		    attribute_description_qm) : Qnil;
	    if (attribute_description_qm)
		set_evaluation_structure_slot(structure,Qicon_reflection,val);
	}
	attribute_description_qm = 
		get_attribute_description_from_class_description(ISVREF(thing,
		(SI_Long)1L),Qicon_variables,Nil);
	val = attribute_description_qm ? 
		get_attribute_description_evaluation_value(thing,
		attribute_description_qm) : Qnil;
	if (attribute_description_qm)
	    set_evaluation_structure_slot(structure,Qicon_variables,val);
	return VALUES_1(structure);
    }
    else
	return VALUES_1(Nil);
}

/* GET-THING-UPDATED-INFO-WITH-ALL-CHILDREN */
Object get_thing_updated_info_with_all_children(thing,result_1,slots_to_update)
    Object thing, result_1, slots_to_update;
{
    Object children_of_thing_qm, item_like_children_qm, first_child_qm, temp;
    Object child1, child2, ab_loop_list_;

    x_note_fn_call(92,112);
    children_of_thing_qm = children_of_thing(1,thing);
    item_like_children_qm = item_like_children(children_of_thing_qm);
    first_child_qm = CAR(item_like_children_qm);
    result_1 = gensym_cons_1(thing,result_1);
    temp = get_thing_updated_info(thing,slots_to_update);
    result_1 = gensym_cons_1(temp,result_1);
    if (first_child_qm && v5_tw_item_like_p(first_child_qm))
	result_1 = get_thing_updated_info_with_all_children(first_child_qm,
		result_1,slots_to_update);
    child1 = Nil;
    child2 = Nil;
    ab_loop_list_ = item_like_children_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    child2 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (child2 && v5_tw_item_like_p(child2))
	result_1 = get_thing_updated_info_with_all_children(child2,
		result_1,slots_to_update);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(children_of_thing_qm);
    reclaim_gensym_list_1(item_like_children_qm);
    return VALUES_1(result_1);
}

/* GET-THING-INITIAL-INFO-WITH-ALL-CHILDREN */
Object get_thing_initial_info_with_all_children(thing,result_1)
    Object thing, result_1;
{
    Object children_of_thing_qm, item_like_children_qm, first_child_qm, temp;
    Object child1, child2, ab_loop_list_;

    x_note_fn_call(92,113);
    children_of_thing_qm = children_of_thing(2,thing,T);
    item_like_children_qm = item_like_children(children_of_thing_qm);
    first_child_qm = CAR(item_like_children_qm);
    if (v5_tw_item_like_p(thing)) {
	result_1 = gensym_cons_1(thing,result_1);
	temp = get_thing_initial_info(thing);
	result_1 = gensym_cons_1(temp,result_1);
    }
    if (first_child_qm && v5_tw_item_like_p(first_child_qm))
	result_1 = get_thing_initial_info_with_all_children(first_child_qm,
		result_1);
    child1 = Nil;
    child2 = Nil;
    ab_loop_list_ = item_like_children_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    child2 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (child2 && v5_tw_item_like_p(child2))
	result_1 = get_thing_initial_info_with_all_children(child2,result_1);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(children_of_thing_qm);
    reclaim_gensym_list_1(item_like_children_qm);
    return VALUES_1(result_1);
}

void view_def_INIT()
{
    Object temp, reclaim_structure_for_access_error_1;
    Object reclaim_structure_for_class_subscriptions_1;
    Object reclaim_structure_for_class_subscription_1;
    Object named_dynamic_extent_description;
    Object reclaim_structure_for_javalink_versioned_call_data_1, temp_1;
    Object reclaim_structure_for_deferred_update_1;
    Object AB_package, string_constant_31, list_constant_4, string_constant_29;
    Object string_constant_15, string_constant_30, Qtc_representation;
    Object Qdeferred_update, Qreclaim_structure;
    Object Qoutstanding_deferred_update_count;
    Object Qdeferred_update_structure_memory_usage, Qutilities2;
    Object string_constant_28, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_27, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_value_reclaimer;
    Object Qreclaim_item_representation_user_data_value_value;
    Object Qitem_representation_user_data_value;
    Object Qreclaim_item_representation_denotation_value;
    Object Qitem_representation_denotation, string_constant_26;
    Object string_constant_25, string_constant_24, Qcallback_representation;
    Object Qreclaim_callback_representation_callback_serial_number_value;
    Object Qcallback_representation_callback_serial_number, string_constant_23;
    Object list_constant_1, string_constant_22, string_constant_21;
    Object list_constant_3, Qview_def, Qmake_representation_handle_table;
    Object Kfuncall;
    Object Qmutate_representation_handle_tree_for_hash_skip_list_entry;
    Object Qout_representation_handle_hash_vector_109_vectors;
    Object Qrepresentation_handle_hash_vector_109_vector_memory_usage;
    Object string_constant_20, list_constant_2, Qlocal_pseudo_socket;
    Object string_constant_19, Qobject_definition_representation;
    Object string_constant_18, Qrepresentation;
    Object Qreclaim_represented_frame_value, Qrepresented_frame;
    Object Qreclaim_representation_address_value, Qrepresentation_address;
    Object string_constant_17, list_constant, string_constant_16, Qsystem_item;
    Object Qjavalink_versioned_call_data;
    Object Qoutstanding_javalink_versioned_call_data_count;
    Object Qjavalink_versioned_call_data_structure_memory_usage;
    Object string_constant_14, string_constant_13;
    Object Qnamed_dynamic_extent_description, string_constant_12;
    Object Qclass_subscription, Qoutstanding_class_subscription_count;
    Object Qclass_subscription_structure_memory_usage, string_constant_11;
    Object string_constant_10, Qclass_subscriptions;
    Object Qoutstanding_class_subscriptions_count;
    Object Qclass_subscriptions_structure_memory_usage, string_constant_9;
    Object string_constant_8, Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qaccess_error, Qoutstanding_access_error_count;
    Object Qaccess_error_structure_memory_usage, string_constant_7;
    Object string_constant_6;

    x_note_fn_call(92,114);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_access_error_g2_struct = 
	    STATIC_SYMBOL("ACCESS-ERROR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qaccess_error = STATIC_SYMBOL("ACCESS-ERROR",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_access_error_g2_struct,
	    Qaccess_error,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qaccess_error,
	    Qg2_defstruct_structure_name_access_error_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_access_error == UNBOUND)
	The_type_description_of_access_error = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83f=y1n83f=y8n8k1l8n0000001l1n8y83-2ly1m83pKy83pLyknk0k0");
    temp = The_type_description_of_access_error;
    The_type_description_of_access_error = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_access_error_g2_struct,
	    The_type_description_of_access_error,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qaccess_error,
	    The_type_description_of_access_error,Qtype_description_of_type);
    Qoutstanding_access_error_count = 
	    STATIC_SYMBOL("OUTSTANDING-ACCESS-ERROR-COUNT",AB_package);
    Qaccess_error_structure_memory_usage = 
	    STATIC_SYMBOL("ACCESS-ERROR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_7 = STATIC_STRING("1q83f=y8s83-J3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_access_error_count);
    push_optimized_constant(Qaccess_error_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_access_errors = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ACCESS-ERRORS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_access_errors,
	    Chain_of_available_access_errors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_access_errors,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qaccess_error_count = STATIC_SYMBOL("ACCESS-ERROR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaccess_error_count,Access_error_count);
    record_system_variable(Qaccess_error_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_access_errors_vector == UNBOUND)
	Chain_of_available_access_errors_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qaccess_error_structure_memory_usage,
	    STATIC_FUNCTION(access_error_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_access_error_count,
	    STATIC_FUNCTION(outstanding_access_error_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_access_error_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_access_error,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qaccess_error,
	    reclaim_structure_for_access_error_1);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("ACCESS-ERROR: ~(~a~)");
    string_constant_1 = STATIC_STRING(" where:~%");
    string_constant_2 = STATIC_STRING("  ~a = ~NV~%");
    Qmissing_implied_attribute = STATIC_SYMBOL("MISSING-IMPLIED-ATTRIBUTE",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    string_constant_3 = STATIC_STRING("~NF");
    Qsymbolic_value = STATIC_SYMBOL("SYMBOLIC-VALUE",AB_package);
    Qconclude_no_value_in_non_variable = 
	    STATIC_SYMBOL("CONCLUDE-NO-VALUE-IN-NON-VARIABLE",AB_package);
    Qno_such_class_error = STATIC_SYMBOL("NO-SUCH-CLASS-ERROR",AB_package);
    Qab_class_name = STATIC_SYMBOL("CLASS-NAME",AB_package);
    Qconclude_into_non_variable_or_parameter = 
	    STATIC_SYMBOL("CONCLUDE-INTO-NON-VARIABLE-OR-PARAMETER",
	    AB_package);
    Qitem_class = STATIC_SYMBOL("ITEM-CLASS",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    string_constant_4 = STATIC_STRING("~NS");
    Qitem_in_attribute = STATIC_SYMBOL("ITEM-IN-ATTRIBUTE",AB_package);
    Qinactive_item_in_attribute = 
	    STATIC_SYMBOL("INACTIVE-ITEM-IN-ATTRIBUTE",AB_package);
    string_constant_5 = STATIC_STRING("~NA");
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qlt_none_gt = STATIC_SYMBOL("<NONE>",AB_package);
    Qattribute_or_structure = STATIC_SYMBOL("ATTRIBUTE-OR-STRUCTURE",
	    AB_package);
    Qattribute_access_on_non_frame = 
	    STATIC_SYMBOL("ATTRIBUTE-ACCESS-ON-NON-FRAME",AB_package);
    Qvirtual_attribute_name = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-NAME",
	    AB_package);
    Qno_such_virtual_attribute = STATIC_SYMBOL("NO-SUCH-VIRTUAL-ATTRIBUTE",
	    AB_package);
    Qclass_subscriptions = STATIC_SYMBOL("CLASS-SUBSCRIPTIONS",AB_package);
    Kb_specific_property_names = CONS(Qclass_subscriptions,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qclass_subscriptions,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Class_subscriptions_kbprop = Qclass_subscriptions;
    Qg2_defstruct_structure_name_class_subscriptions_g2_struct = 
	    STATIC_SYMBOL("CLASS-SUBSCRIPTIONS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_subscriptions_g2_struct,
	    Qclass_subscriptions,Qab_name_of_unique_structure_type);
    mutate_global_property(Qclass_subscriptions,
	    Qg2_defstruct_structure_name_class_subscriptions_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_class_subscriptions == UNBOUND)
	The_type_description_of_class_subscriptions = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83fuy1n83fuy8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_class_subscriptions;
    The_type_description_of_class_subscriptions = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    mutate_global_property(Qg2_defstruct_structure_name_class_subscriptions_g2_struct,
	    The_type_description_of_class_subscriptions,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qclass_subscriptions,
	    The_type_description_of_class_subscriptions,
	    Qtype_description_of_type);
    Qoutstanding_class_subscriptions_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-SUBSCRIPTIONS-COUNT",AB_package);
    Qclass_subscriptions_structure_memory_usage = 
	    STATIC_SYMBOL("CLASS-SUBSCRIPTIONS-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q83fuy8s83-Mdy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_subscriptions_count);
    push_optimized_constant(Qclass_subscriptions_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_class_subscriptionss = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLASS-SUBSCRIPTIONSS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_class_subscriptionss,
	    Chain_of_available_class_subscriptionss);
    record_system_variable(Qchain_of_available_class_subscriptionss,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qclass_subscriptions_count = STATIC_SYMBOL("CLASS-SUBSCRIPTIONS-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_subscriptions_count,
	    Class_subscriptions_count);
    record_system_variable(Qclass_subscriptions_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_class_subscriptionss_vector == UNBOUND)
	Chain_of_available_class_subscriptionss_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclass_subscriptions_structure_memory_usage,
	    STATIC_FUNCTION(class_subscriptions_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_class_subscriptions_count,
	    STATIC_FUNCTION(outstanding_class_subscriptions_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_class_subscriptions_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_class_subscriptions,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qclass_subscriptions,
	    reclaim_structure_for_class_subscriptions_1);
    Qg2_defstruct_structure_name_class_subscription_g2_struct = 
	    STATIC_SYMBOL("CLASS-SUBSCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qclass_subscription = STATIC_SYMBOL("CLASS-SUBSCRIPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_class_subscription_g2_struct,
	    Qclass_subscription,Qab_name_of_unique_structure_type);
    mutate_global_property(Qclass_subscription,
	    Qg2_defstruct_structure_name_class_subscription_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_class_subscription == UNBOUND)
	The_type_description_of_class_subscription = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83fty1n83fty8n8k1l8n0000001l1n8y83-3By1n83s1y83s2y83s3ykok0k0");
    temp = The_type_description_of_class_subscription;
    The_type_description_of_class_subscription = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_class_subscription_g2_struct,
	    The_type_description_of_class_subscription,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qclass_subscription,
	    The_type_description_of_class_subscription,
	    Qtype_description_of_type);
    Qoutstanding_class_subscription_count = 
	    STATIC_SYMBOL("OUTSTANDING-CLASS-SUBSCRIPTION-COUNT",AB_package);
    Qclass_subscription_structure_memory_usage = 
	    STATIC_SYMBOL("CLASS-SUBSCRIPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83fty8s83-Mcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_class_subscription_count);
    push_optimized_constant(Qclass_subscription_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_class_subscriptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLASS-SUBSCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_class_subscriptions,
	    Chain_of_available_class_subscriptions);
    record_system_variable(Qchain_of_available_class_subscriptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qclass_subscription_count = STATIC_SYMBOL("CLASS-SUBSCRIPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_subscription_count,
	    Class_subscription_count);
    record_system_variable(Qclass_subscription_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_class_subscriptions_vector == UNBOUND)
	Chain_of_available_class_subscriptions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qclass_subscription_structure_memory_usage,
	    STATIC_FUNCTION(class_subscription_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_class_subscription_count,
	    STATIC_FUNCTION(outstanding_class_subscription_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_class_subscription_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_class_subscription,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qclass_subscription,
	    reclaim_structure_for_class_subscription_1);
    Qrepresentation_callback_remote_procedure_name = 
	    STATIC_SYMBOL("REPRESENTATION-CALLBACK-REMOTE-PROCEDURE-NAME",
	    AB_package);
    Representation_callback_remote_procedure_name_prop = 
	    Qrepresentation_callback_remote_procedure_name;
    string_constant_12 = STATIC_STRING("JAVALINK-NOTIFICATION-VERSIONS");
    if (Javalink_notification_versions == UNBOUND)
	Javalink_notification_versions = make_recursive_lock(2,Kname,
		string_constant_12);
    Qjavalink_notification_versions = 
	    STATIC_SYMBOL("JAVALINK-NOTIFICATION-VERSIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjavalink_notification_versions,
	    Javalink_notification_versions);
    Qview_def = STATIC_SYMBOL("VIEW-DEF",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qjavalink_notification_versions,
	    Qview_def,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qjavalink_notification_versions,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct = 
	    STATIC_SYMBOL("JAVALINK-VERSIONED-CALL-DATA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qjavalink_versioned_call_data = 
	    STATIC_SYMBOL("JAVALINK-VERSIONED-CALL-DATA",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct,
	    Qjavalink_versioned_call_data,Qab_name_of_unique_structure_type);
    mutate_global_property(Qjavalink_versioned_call_data,
	    Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_javalink_versioned_call_data == UNBOUND)
	The_type_description_of_javalink_versioned_call_data = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83k5y1n83k5y8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_javalink_versioned_call_data;
    The_type_description_of_javalink_versioned_call_data = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_javalink_versioned_call_data_g2_struct,
	    The_type_description_of_javalink_versioned_call_data,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qjavalink_versioned_call_data,
	    The_type_description_of_javalink_versioned_call_data,
	    Qtype_description_of_type);
    Qoutstanding_javalink_versioned_call_data_count = 
	    STATIC_SYMBOL("OUTSTANDING-JAVALINK-VERSIONED-CALL-DATA-COUNT",
	    AB_package);
    Qjavalink_versioned_call_data_structure_memory_usage = 
	    STATIC_SYMBOL("JAVALINK-VERSIONED-CALL-DATA-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83k5y8s83-bXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_javalink_versioned_call_data_count);
    push_optimized_constant(Qjavalink_versioned_call_data_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_javalink_versioned_call_datas = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-JAVALINK-VERSIONED-CALL-DATAS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_javalink_versioned_call_datas,
	    Chain_of_available_javalink_versioned_call_datas);
    record_system_variable(Qchain_of_available_javalink_versioned_call_datas,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qjavalink_versioned_call_data_count = 
	    STATIC_SYMBOL("JAVALINK-VERSIONED-CALL-DATA-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjavalink_versioned_call_data_count,
	    Javalink_versioned_call_data_count);
    record_system_variable(Qjavalink_versioned_call_data_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_javalink_versioned_call_datas_vector == UNBOUND)
	Chain_of_available_javalink_versioned_call_datas_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qjavalink_versioned_call_data_structure_memory_usage,
	    STATIC_FUNCTION(javalink_versioned_call_data_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_javalink_versioned_call_data_count,
	    STATIC_FUNCTION(outstanding_javalink_versioned_call_data_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_javalink_versioned_call_data_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_javalink_versioned_call_data,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qjavalink_versioned_call_data,
	    reclaim_structure_for_javalink_versioned_call_data_1);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrepresentation = STATIC_SYMBOL("REPRESENTATION",AB_package);
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    list_constant = STATIC_CONS(Qsystem_item,Qnil);
    check_if_superior_classes_are_defined(Qrepresentation,list_constant);
    string_constant_15 = STATIC_STRING("1l1l8t");
    string_constant_16 = 
	    STATIC_STRING("1m4z8r83Z-y83Z-y836By836By00001m1l8l1l8o000004z8r83Z*y83Z*y836By836By00001m1l8l1l8o00000");
    string_constant_17 = 
	    STATIC_STRING("1o8q1n836By1l833ay8t1n83Z-y08o1n83Z*y08o");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_16);
    add_class_to_environment(9,Qrepresentation,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,
	    regenerate_optimized_constant(string_constant_17),Nil);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qrepresentation_address = STATIC_SYMBOL("REPRESENTATION-ADDRESS",
	    AB_package);
    Qreclaim_representation_address_value = 
	    STATIC_SYMBOL("RECLAIM-REPRESENTATION-ADDRESS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_representation_address_value,
	    STATIC_FUNCTION(reclaim_representation_address_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qrepresentation_address,
	    SYMBOL_FUNCTION(Qreclaim_representation_address_value),
	    Qslot_value_reclaimer);
    Qrepresented_frame = STATIC_SYMBOL("REPRESENTED-FRAME",AB_package);
    Qreclaim_represented_frame_value = 
	    STATIC_SYMBOL("RECLAIM-REPRESENTED-FRAME-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_represented_frame_value,
	    STATIC_FUNCTION(reclaim_represented_frame_value,NIL,FALSE,2,2));
    mutate_global_property(Qrepresented_frame,
	    SYMBOL_FUNCTION(Qreclaim_represented_frame_value),
	    Qslot_value_reclaimer);
    Qobject_definition_representation = 
	    STATIC_SYMBOL("OBJECT-DEFINITION-REPRESENTATION",AB_package);
    list_constant_1 = STATIC_CONS(Qrepresentation,Qnil);
    check_if_superior_classes_are_defined(Qobject_definition_representation,
	    list_constant_1);
    string_constant_18 = 
	    STATIC_STRING("1l4z8r83X3y83X3y83X2y83X2y00001m1l8l1l8o00000");
    string_constant_19 = STATIC_STRING("1n8q1n83X2y1l836By8t1n83X3y08o");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_18);
    add_class_to_environment(9,Qobject_definition_representation,
	    list_constant_1,Nil,temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_19),Nil);
    Qlocal_pseudo_socket = STATIC_SYMBOL("LOCAL-PSEUDO-SOCKET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_pseudo_socket,Local_pseudo_socket);
    list_constant_2 = STATIC_CONS(Qlocal_pseudo_socket,Qnil);
    Local_pseudo_socket = list_constant_2;
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qavailable_representation_handle_hash_vector_109_vectors = 
	    STATIC_SYMBOL("AVAILABLE-REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_representation_handle_hash_vector_109_vectors,
	    Available_representation_handle_hash_vector_109_vectors);
    record_system_variable(Qavailable_representation_handle_hash_vector_109_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_representation_handle_hash_vector_109_vectors = 
	    STATIC_SYMBOL("COUNT-OF-REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_representation_handle_hash_vector_109_vectors,
	    Count_of_representation_handle_hash_vector_109_vectors);
    record_system_variable(Qcount_of_representation_handle_hash_vector_109_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_representation_handle_hash_vector_109_vectors_vector == 
	    UNBOUND)
	Available_representation_handle_hash_vector_109_vectors_vector = 
		make_thread_array(Nil);
    Qout_representation_handle_hash_vector_109_vectors = 
	    STATIC_SYMBOL("OUT-REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTORS",
	    AB_package);
    Qrepresentation_handle_hash_vector_109_vector_memory_usage = 
	    STATIC_SYMBOL("REPRESENTATION-HANDLE-HASH-VECTOR-109-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_20 = STATIC_STRING("1q83-mKy83*9y83-P7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_representation_handle_hash_vector_109_vectors);
    push_optimized_constant(Qrepresentation_handle_hash_vector_109_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    SET_SYMBOL_FUNCTION(Qrepresentation_handle_hash_vector_109_vector_memory_usage,
	    STATIC_FUNCTION(representation_handle_hash_vector_109_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_representation_handle_hash_vector_109_vectors,
	    STATIC_FUNCTION(out_representation_handle_hash_vector_109_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_representation_handle_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-REPRESENTATION-HANDLE-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_representation_handle_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_representation_handle_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_representation_handle_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_representation_handle_tree_for_hash_skip_list_entry);
    Qrepresentation_handle_tree_for_hash = 
	    STATIC_SYMBOL("REPRESENTATION-HANDLE-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qthe_representation_handle_hashtable = 
	    STATIC_SYMBOL("THE-REPRESENTATION-HANDLE-HASHTABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthe_representation_handle_hashtable,
	    The_representation_handle_hashtable);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_representation_handle_table = 
	    STATIC_SYMBOL("MAKE-REPRESENTATION-HANDLE-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_representation_handle_table,
	    STATIC_FUNCTION(make_representation_handle_table,NIL,FALSE,0,0));
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_representation_handle_table);
    record_system_variable(Qthe_representation_handle_hashtable,Qview_def,
	    list_constant_3,Qnil,Qnil,Qnil,Qnil);
    if (Current_callback_representation_subscription_handle == UNBOUND)
	Current_callback_representation_subscription_handle = FIX((SI_Long)0L);
    Qcallback_representation = STATIC_SYMBOL("CALLBACK-REPRESENTATION",
	    AB_package);
    check_if_superior_classes_are_defined(Qcallback_representation,
	    list_constant_1);
    string_constant_21 = 
	    STATIC_STRING("1n4z8r83Hby83Hby830Xy830Xy00001m1l8l1l8o000004z8r83Hcy83Hcy830Xy830Xy00001m1l8l1l8o000004z8r83Hdy83Hdy830Xy830Xy00001m1l8l1l8o00");
    string_constant_22 = STATIC_STRING("000");
    string_constant_23 = 
	    STATIC_STRING("1p8q1n830Xy1l836By8t1n83Hby08o1n83Hcy08o1n83Hdy08o");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_21,
	    string_constant_22));
    add_class_to_environment(9,Qcallback_representation,list_constant_1,
	    Nil,temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_23),Nil);
    Qcallback_representation_callback_serial_number = 
	    STATIC_SYMBOL("CALLBACK-REPRESENTATION-CALLBACK-SERIAL-NUMBER",
	    AB_package);
    Qreclaim_callback_representation_callback_serial_number_value = 
	    STATIC_SYMBOL("RECLAIM-CALLBACK-REPRESENTATION-CALLBACK-SERIAL-NUMBER-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_callback_representation_callback_serial_number_value,
	    STATIC_FUNCTION(reclaim_callback_representation_callback_serial_number_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcallback_representation_callback_serial_number,
	    SYMBOL_FUNCTION(Qreclaim_callback_representation_callback_serial_number_value),
	    Qslot_value_reclaimer);
    Qitem_representation = STATIC_SYMBOL("ITEM-REPRESENTATION",AB_package);
    list_constant_4 = STATIC_CONS(Qcallback_representation,Qnil);
    check_if_superior_classes_are_defined(Qitem_representation,
	    list_constant_4);
    string_constant_24 = 
	    STATIC_STRING("1n4z8r83Swy83Swy83Svy83Svy00001m1l8l1l8o000004z8r83T+y83T+y83Svy83Svy08k001m1l8l1l8o000004z8r83Sxy83Sxy83Svy83Svy00001m1l8l1l8o0");
    string_constant_25 = STATIC_STRING("0000");
    string_constant_26 = 
	    STATIC_STRING("1p8q1n83Svy1l830Xy8t1n83Swy08o1n83T+y8k8o1n83Sxy08o");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_24,
	    string_constant_25));
    add_class_to_environment(9,Qitem_representation,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_26),Nil);
    Qitem_representation_denotation = 
	    STATIC_SYMBOL("ITEM-REPRESENTATION-DENOTATION",AB_package);
    Qreclaim_item_representation_denotation_value = 
	    STATIC_SYMBOL("RECLAIM-ITEM-REPRESENTATION-DENOTATION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_item_representation_denotation_value,
	    STATIC_FUNCTION(reclaim_item_representation_denotation_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qitem_representation_denotation,
	    SYMBOL_FUNCTION(Qreclaim_item_representation_denotation_value),
	    Qslot_value_reclaimer);
    Qitem_representation_user_data_value = 
	    STATIC_SYMBOL("ITEM-REPRESENTATION-USER-DATA-VALUE",AB_package);
    Qreclaim_item_representation_user_data_value_value = 
	    STATIC_SYMBOL("RECLAIM-ITEM-REPRESENTATION-USER-DATA-VALUE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_item_representation_user_data_value_value,
	    STATIC_FUNCTION(reclaim_item_representation_user_data_value_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qitem_representation_user_data_value,
	    SYMBOL_FUNCTION(Qreclaim_item_representation_user_data_value_value),
	    Qslot_value_reclaimer);
    Qws_representation = STATIC_SYMBOL("WS-REPRESENTATION",AB_package);
    Qitem_color_pattern_change = STATIC_SYMBOL("ITEM-COLOR-PATTERN-CHANGE",
	    AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qcustom_event = STATIC_SYMBOL("CUSTOM-EVENT",AB_package);
    Qadd_item_to_workspace = STATIC_SYMBOL("ADD-ITEM-TO-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qadd_item_to_workspace,
	    STATIC_FUNCTION(add_item_to_workspace,NIL,TRUE,4,5));
    Qremove_item_from_workspace = 
	    STATIC_SYMBOL("REMOVE-ITEM-FROM-WORKSPACE",AB_package);
    Qmodify = STATIC_SYMBOL("MODIFY",AB_package);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Qby_copy_with_handle = STATIC_SYMBOL("BY-COPY-WITH-HANDLE",AB_package);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qg2_defstruct_structure_name_deferred_update_g2_struct = 
	    STATIC_SYMBOL("DEFERRED-UPDATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdeferred_update = STATIC_SYMBOL("DEFERRED-UPDATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_deferred_update_g2_struct,
	    Qdeferred_update,Qab_name_of_unique_structure_type);
    mutate_global_property(Qdeferred_update,
	    Qg2_defstruct_structure_name_deferred_update_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_deferred_update == UNBOUND)
	The_type_description_of_deferred_update = Nil;
    string_constant_27 = 
	    STATIC_STRING("43Dy8m83gZy1n83gZy8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_deferred_update;
    The_type_description_of_deferred_update = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_27));
    mutate_global_property(Qg2_defstruct_structure_name_deferred_update_g2_struct,
	    The_type_description_of_deferred_update,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qdeferred_update,
	    The_type_description_of_deferred_update,Qtype_description_of_type);
    Qoutstanding_deferred_update_count = 
	    STATIC_SYMBOL("OUTSTANDING-DEFERRED-UPDATE-COUNT",AB_package);
    Qdeferred_update_structure_memory_usage = 
	    STATIC_SYMBOL("DEFERRED-UPDATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_28 = STATIC_STRING("1q83gZy8s83-Qay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_deferred_update_count);
    push_optimized_constant(Qdeferred_update_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_28));
    Qchain_of_available_deferred_updates = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DEFERRED-UPDATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_deferred_updates,
	    Chain_of_available_deferred_updates);
    record_system_variable(Qchain_of_available_deferred_updates,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qdeferred_update_count = STATIC_SYMBOL("DEFERRED-UPDATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdeferred_update_count,Deferred_update_count);
    record_system_variable(Qdeferred_update_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_deferred_updates_vector == UNBOUND)
	Chain_of_available_deferred_updates_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdeferred_update_structure_memory_usage,
	    STATIC_FUNCTION(deferred_update_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_deferred_update_count,
	    STATIC_FUNCTION(outstanding_deferred_update_count,NIL,FALSE,0,0));
    reclaim_structure_for_deferred_update_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_deferred_update,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdeferred_update,
	    reclaim_structure_for_deferred_update_1);
    Qtc_representation = STATIC_SYMBOL("TC-REPRESENTATION",AB_package);
    check_if_superior_classes_are_defined(Qtc_representation,list_constant_4);
    string_constant_29 = STATIC_STRING("0");
    string_constant_30 = STATIC_STRING("1m8q1n83-ETy1l830Xy8t");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_29);
    add_class_to_environment(9,Qtc_representation,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_30),Nil);
    check_if_superior_classes_are_defined(Qws_representation,list_constant_4);
    string_constant_31 = STATIC_STRING("1m8q1n83-H4y1l830Xy8t");
    temp = regenerate_optimized_constant(string_constant_15);
    temp_1 = regenerate_optimized_constant(string_constant_29);
    add_class_to_environment(9,Qws_representation,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_31),Nil);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qworkspace_dimensions = STATIC_SYMBOL("WORKSPACE-DIMENSIONS",AB_package);
    Qworkspace_background_color = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qworkspace_foreground_color = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR",AB_package);
    Qitem_info_list = STATIC_SYMBOL("ITEM-INFO-LIST",AB_package);
    Qitem_data_list = STATIC_SYMBOL("ITEM-DATA-LIST",AB_package);
    Qrepresentation_type = STATIC_SYMBOL("REPRESENTATION-TYPE",AB_package);
    Qitem_color_pattern = STATIC_SYMBOL("ITEM-COLOR-PATTERN",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qconnection_is_directed = STATIC_SYMBOL("CONNECTION-IS-DIRECTED",
	    AB_package);
    Qconnection_position_sequence = 
	    STATIC_SYMBOL("CONNECTION-POSITION-SEQUENCE",AB_package);
    Qrepresented_item = STATIC_SYMBOL("REPRESENTED-ITEM",AB_package);
    Qformat_type = STATIC_SYMBOL("FORMAT-TYPE",AB_package);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qtable_cells = STATIC_SYMBOL("TABLE-CELLS",AB_package);
    Qdefault_cell_format = STATIC_SYMBOL("DEFAULT-CELL-FORMAT",AB_package);
    Qtable_font_size = STATIC_SYMBOL("TABLE-FONT-SIZE",AB_package);
    Qitem_configuration = STATIC_SYMBOL("ITEM-CONFIGURATION",AB_package);
    Qmanually_disabled_qm = STATIC_SYMBOL("MANUALLY-DISABLED\?",AB_package);
    Qtext_x_magnification = STATIC_SYMBOL("TEXT-X-MAGNIFICATION",AB_package);
    Qtext_y_magnification = STATIC_SYMBOL("TEXT-Y-MAGNIFICATION",AB_package);
    Qitem_x_position = STATIC_SYMBOL("ITEM-X-POSITION",AB_package);
    Qitem_y_position = STATIC_SYMBOL("ITEM-Y-POSITION",AB_package);
    Qitem_width = STATIC_SYMBOL("ITEM-WIDTH",AB_package);
    Qitem_height = STATIC_SYMBOL("ITEM-HEIGHT",AB_package);
    Qicon_heading = STATIC_SYMBOL("ICON-HEADING",AB_package);
    Qicon_reflection = STATIC_SYMBOL("ICON-REFLECTION",AB_package);
    Qicon_variables = STATIC_SYMBOL("ICON-VARIABLES",AB_package);
}
