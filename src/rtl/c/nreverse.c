/*
 * nreverse.c -  Chestnut Run-Time Library entry for function nreverse
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
extern Object elt(Object,Object);
extern long ilength(Object sequence);
extern Object set_elt(Object,Object,Object);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object elt();
extern long ilength();
extern Object set_elt();

#endif




Object nreverse (sequence)
    Object sequence;
{
    Declare_local_temp;
    long i, j, len, halflen;
    char *str, tempc;
    Object prev_cell = NIL, tempelt, next_cell;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(sequence);

    if (STRINGP(sequence)) {
	len = ilength(sequence);
	halflen = len / 2L;
	str = ISTRING(sequence);
	for (i = 0, j = len-1; i < halflen; i++, j--) {
	    tempc = str[i];
	    str[i] = str[j];
	    str[j] = tempc;
	}
	RESTORE_STACK();
	return VALUES_1(sequence);
    }
    else if (VECTORP(sequence)) {
	len = ilength(sequence);
	halflen = len/2;
	for (i = 0, j = len-1; i < halflen; i++, j--) {
	    tempelt = elt(sequence, FIX(i));
	    (void)set_elt(sequence, FIX(i), elt(sequence, FIX(j)));
	    (void)set_elt(sequence, FIX(j), tempelt);
	}
	RESTORE_STACK();
	return VALUES_1(sequence);
    }
    else if (LISTP(sequence)) {
	while (!ENDP(sequence)) {
	    next_cell = M_CDR(sequence);
	    RPLACD(sequence, prev_cell);
	    prev_cell = sequence;
	    sequence = next_cell;
	}   
	RESTORE_STACK();
	return VALUES_1(prev_cell);
    }
    else {
	(Object) error(2, "nreverse: invalid argument - ~s", sequence);
	return VALUES_1(NIL); /* NOT REACHED */
    }
}
