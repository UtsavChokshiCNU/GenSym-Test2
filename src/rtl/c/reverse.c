/*
 * reverse.c -  Chestnut Run-Time Library entry for function reverse
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object array_element_type(Object);
extern Object cons(Object,Object);
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object length(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_string(Object size, Object initial_element);
extern Object set_elt(Object,Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object array_element_type();
extern Object cons();
extern Object elt();
extern long ilength();
extern Object length();
extern Object make_array();
extern Object make_string();
extern Object set_elt();

#endif




Object reverse (sequence)
    Object sequence;
{
    Declare_local_temp;
    long i, j, len;
    char *src, *dst;
    Object prev_cell = NIL, new_cell, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(sequence,prev_cell);
    PROTECTI_2(new_cell,result);
    if (STRINGP(sequence)) {
	len = ilength(sequence);
	src = ISTRING(sequence);
	result = make_string(FIX(len), KOPT);
	dst = ISTRING(result);
	for (i = 0, j = len-1; i < len; i++, j--) {
	    dst[i] = src[j];
	}
	dst[i] = '\0';
    }
    else if (VECTORP(sequence)) {
	result = make_array(length(sequence),
			    array_element_type(sequence), KOPT, KOPT,
			    NIL, NIL, NIL, KOPT);
	len = ilength(sequence);
	for (i = 0, j = len-1; i < len; i++, j--)
	    (void) set_elt(result, FIX(i), elt(sequence, FIX(j)));
    }
    else if (LISTP(sequence)) {
	while (!ENDP(sequence)) {
	    new_cell = cons(M_CAR(sequence), prev_cell);
	    prev_cell = new_cell;
	    sequence = M_CDR(sequence);
	}
	result = prev_cell;
    }
    else
	error(2, "reverse: bad arg - ~s", sequence);

    RESTORE_STACK();
    return VALUES_1(result);
}
