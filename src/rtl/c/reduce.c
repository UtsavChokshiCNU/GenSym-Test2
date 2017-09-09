/*
 * reduce.c -  Chestnut Run-Time Library entry for function reduce
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object elt(Object,Object);
extern Object funcall0(Object func);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);

#else

extern Object elt();
extern Object funcall0();
extern Object funcall2();
extern long ilength();

#endif




Object reduce (function, sequence, from_end, lstart, lend, initial_value)
    Object function, sequence, from_end, lstart, lend, initial_value;
{
    Declare_local_temp;
    long start, end, len;
    Object result = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(function,sequence,initial_value);
    PROTECTI_1(result);
    /* check for special case */
    if (UNSUPPLIED_P(initial_value) && !TRUEP(sequence)) {
	result = FUNCALL_0(function);
	goto LABEL1;
    }
    /* assume: start is inclusive, end is exclusive */
    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(sequence);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    if (UNSUPPLIED_P(from_end)) from_end = NIL;

    if (!TRUEP(from_end)) {  /* forward */
	if (SUPPLIEDP(initial_value))
	    result = initial_value;
	else {
	    result = elt(sequence, FIX(start));
	    start++;
	}
	while (start < end) {
	    result = FUNCALL_2(function, result, elt(sequence, FIX(start)));
	    start++;
	}
    }
    else {
	end--;
	if (SUPPLIEDP(initial_value))
	    result = initial_value;
	else {
	    result = elt(sequence, FIX(end));
	    end--;
	}
	while (end >= start) {
	    result = FUNCALL_2(function, elt(sequence, FIX(end)), result);
	    end--;
	}
    }

    LABEL1:
    RESTORE_STACK();
    return VALUES_1(result);
}
