/*
 * nconc.c -  Chestnut Run-Time Library entry for function nconc
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object last(Object,Object);

#else

extern Object last();

#endif


#include "lists.h"

Object nconc varargs_1(int, n)
{
    Declare_local_temp;
    va_list ap;
    Object result = NIL, last_conc_arg = NIL;
    Object next_arg, spot;

    /* No GC protection needed, because this doesn't cons. */
    SI_va_start(ap,n);
    while (n--) {
        next_arg = va_arg(ap, Object);
	if (TRUEP(next_arg)) {	/* skip NIL args */
	    if (ENDP(result))
		result = next_arg;	/* first non-NIL arg */
	    else {
		/* prev non-NIL args were encountered.  Splice next_arg
		 * onto the end of them.  This logic avoids having to
		 * traverse the last arg on arglist
		 */
		spot = last(last_conc_arg, KOPT);
		RPLACD(spot, next_arg);
	    }
	    last_conc_arg = next_arg;
	}
    }
    va_end(ap);
    return VALUES_1(result);
}
