/*
 * mksqunc.c -  Chestnut Run-Time Library entry for function make_sequence
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qarray;
extern Object Qlist;
extern Object Qsimple_string;
extern Object Qsimple_vector;
extern Object Qstring_char;
extern Object Qstring;
extern Object Qvector;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object cons(Object,Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();
extern Object cons();
extern Object make_array();

#endif




Object make_sequence (type, lsize, initial_element)
    Object type, lsize, initial_element;
{
    Declare_local_temp;
    Object result, temp;
    long size;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(type,lsize,initial_element);
    PROTECTI_2(result,temp);
    if (EQ(type, Qlist)) {
	result = NIL;
	size = IFIX(lsize);
	while (size--)
	    result = cons(initial_element, result);
    }
    else if (EQ(type, Qvector) || EQ(type, Qarray)
	     || EQ(type, Qsimple_vector))
	result = make_array(lsize, T, initial_element, KOPT,KOPT,KOPT,KOPT,KOPT);
    else if (EQ(type, Qstring) || EQ(type, Qsimple_string))
	result = make_array(lsize, Qstring_char, initial_element, KOPT,KOPT,KOPT,KOPT,KOPT);
    else if (CONSP(type)) {
	temp = M_CAR(type);
	if (EQ(temp, Qvector) || EQ(temp, Qarray))
	    result = make_array(lsize, M_SECOND(type), initial_element, KOPT,KOPT,KOPT,KOPT,KOPT);
	else
	    error(2, "make_sequence: unrecognized type - ~s", type);
    }
    else {
	warn(2, "make_sequence: unrecognized type - ~s", type);
	result = make_array(lsize, T, initial_element, KOPT,KOPT,KOPT,KOPT,KOPT);
    }

    RESTORE_STACK();
    return VALUES_1(result);
}
