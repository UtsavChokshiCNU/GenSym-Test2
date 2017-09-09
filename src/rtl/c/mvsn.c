/*
 * mvsn.c -  Chestnut Run-Time Library entry for function mvsn
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];


/* multiple-value-setq */

Object mvsn varargs_1(int, nargs)
{
    Declare_local_temp;
    va_list ap;
    register long i;
    Object value1, *arg;

    if (nargs) {
	SI_va_start(ap,nargs);
	value1 = va_arg(ap, Object);
	--nargs;
	if (nargs) {
	    arg = (Object *) va_arg(ap, Object *);
	    *arg = value1;
	}
	for (i = 0; --nargs; i++) {
	    arg = (Object *) va_arg(ap, Object *);
	    if (i+1 < Values_count)
		*arg = Values[i];
	    else
		*arg = NIL;
	}
	va_end(ap);
	return(VALUES_1(value1));
    }
    return(VALUES_0());
}
