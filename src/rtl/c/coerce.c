/*
 * coerce.c -  Chestnut Run-Time Library entry for function coerce
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qbit_vector;
extern Object Qbit;
extern Object Qcharacter;
extern Object Qdouble_float;
extern Object Qfixnum;
extern Object Qfloat;
extern Object Qlist;
extern Object Qlong_float;
extern Object Qshort_float;
extern Object Qsimple_bit_vector;
extern Object Qsimple_string;
extern Object Qsingle_float;
extern Object Qstring_char;
extern Object Qstring;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object cdouble_to_double(double a);
extern Object cons(Object,Object);
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object int_char(Object n);
extern SI_Long integer_to_long(Object n);
extern char *isymbol_name(Object sym);
extern Object length(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object nreverse(Object);
extern double object_to_cdouble(Object n);
extern Object sequence_type_p(Object rtype);
extern Object typep(Object,Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern Object cdouble_to_double();
extern Object cons();
extern Object elt();
extern long ilength();
extern Object int_char();
extern SI_Long integer_to_long();
extern char *isymbol_name();
extern Object length();
extern Object make_array();
extern Object nreverse();
extern double object_to_cdouble();
extern Object sequence_type_p();
extern Object typep();

#endif



static Object coerce_to_character();
static Object coerce_to_sequence();

/*
 * CLtL specifies only the following cases:
 *  . Coercion between arbitrary sequence types
 *  . Coercion of integers and length-1 strings to characters 
 *  . Coercion of non-complex numbers to one of the four float types
 *  . Coercion of arbitrary numbers to complex
 *  . Coercion to T
 *  . (X3J13) Coercion of symbols and lambda-expressions to FUNCTION
 */

Object coerce (object, result_type)
    Object object;
    Object result_type;
{
    Declare_local_temp;
    SI_Long i;
    Object result;

    if (typep(object, result_type, KOPT) || EQ(result_type, T))
	result = object;
    else if (EQ(result_type, Qfixnum)) {
	if (FIXNUMP(object))
	    result = object;
	else if (NUMBERP(object)) {
	    i = integer_to_long(object);
	    result = FIX(i);
	}
	else {
	    warn(4, "coerce: invalid arguments - ~s, ~s; returning ~s",
	            object, result_type, object);
	    result = object;
	}
    }
    else if (EQ(result_type, Qfloat) ||
	     EQ(result_type, Qdouble_float) || EQ(result_type,Qlong_float) ||
	     EQ(result_type, Qsingle_float) || EQ(result_type,Qshort_float))
	result = cdouble_to_double(object_to_cdouble(object));
    else if (sequence_type_p(result_type))
	result = coerce_to_sequence(object, result_type);
    else if (EQ(result_type, Qcharacter))
	result = coerce_to_character(object, result_type);
/*  else if (EQ(result_type, Qfunction))
	result = coerce_function(object);    */
    else {
	warn(4, "coerce: invalid arguments - ~s, ~s; returning ~s",
	     object, result_type, object);
	result = object;
    }
    return VALUES_1(result);
}


static Object coerce_to_character (object, rtype)
    Object object, rtype;
{
    Declare_local_temp;
    Object result;
    char *name;

    if (STRINGP(object) && ilength(object) == 1L)
	result = elt(object, ZERO);
    else if (SYMBOLP(object) && (name = isymbol_name(object)) &&
		name[1] == '\0')
	result = CHR(name[0]);
    else if (FIXNUMP(object))
	result = int_char(object);
    else
	error(3, "coerce_to_character: invalid arguments - ~S, ~S",
	      object, rtype);
    return VALUES_1(result);
}

/* This routine is only called in the case that typep(object, result_type)
   is NIL */

static Object coerce_to_sequence (object, result_type)
    Object object, result_type;
{
    Declare_local_temp;
    Object orig_obj = object;
    Object result = NIL;
    long ii, ilen;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(object, result_type, orig_obj, result);
    PROTECTI_3(carval,i,len);

    if (CONSP(result_type))
	/* Caller has already ensured that CAR(result_type) is one of
	   VECTOR, SIMPLE-VECTOR, Karray, or SIMPLE-ARRAY */
	result = make_array(length(object),M_SECOND(result_type),
			     KOPT,object,KOPT,KOPT,KOPT,KOPT);
    else if (EQ(result_type, Qstring) || EQ(result_type, Qsimple_string))
	result = make_array(length(object),Qstring_char,
			    KOPT,object,KOPT,KOPT,KOPT,KOPT);
    else if (EQ(result_type, Qbit_vector) ||
	     EQ(result_type, Qsimple_bit_vector))
	result = make_array(length(object),Qbit,
			    KOPT,object,KOPT,KOPT,KOPT,KOPT);
    else if (EQ(result_type, Qlist)) {
	result = NIL;
	ilen = ilength(object);
	for (ii = 0; ii < ilen; ii++) {
	    result = cons(elt(object,FIX(ii)),result);
	}
	result = nreverse(result);
    }
    else {
	result = make_array(length(object),result_type,
				 KOPT,object,KOPT,KOPT,KOPT,KOPT);
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

