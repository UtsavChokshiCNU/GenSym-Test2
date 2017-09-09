/*
 * append.c -  Chestnut Run-Time Library entry for function append
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object ncons1(Object a);

#else

extern Object ncons1();

#endif


#include "lists.h"

Object append varargs_1(int, n)
{
    Declare_local_temp;
    Object result, result_last, copy_arg, new_cell, *rest;
    long i;
    Declare_stack_pointer;

    SAVE_STACK();
    SETUP_REST(n, rest);
    PROTECTI_4(result, result_last, copy_arg, new_cell);

    if (n == 0) {
	result = NIL;
    }
    else if (n == 1) {
	result = rest[0];
    }
    else {
	n -= 1L;
	result = NIL;		/* starting cell of resulting list */
	result_last = NIL;	/* last cell of result, if any non-NIL
				 * arguments yet encountered, else NIL */
        /* copy all but last argument, keeping track of result_last */
	for (i = 0; i < n; ++i) {
	    /* loop is set up to process all but the last argument */
	    copy_arg = rest[i];	/* get next arg */
            if (CONSP(copy_arg)) {
	        if (!TRUEP(result)) {
		    result = result_last = ncons1(M_CAR(copy_arg));
		    copy_arg = M_CDR(copy_arg);
	        }
	        /* copy copy_arg into result, keeping track of result_last */
	        while(CONSP(copy_arg)) {
		    new_cell = ncons1(M_CAR(copy_arg));
		    RPLACD(result_last, new_cell);
		    result_last = new_cell;
		    copy_arg = M_CDR(copy_arg);
	        }
	    }
        }
        /* now splice last argument into result_last */
        if (ENDP(result)) 
	    result = rest[n];  /* n is nargs - 1 */
        else {
	    copy_arg = rest[n];
	    RPLACD(result_last, copy_arg);
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
