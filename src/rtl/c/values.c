/*
 * values.c -  Chestnut Run-Time Library entry for function values
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];



Object values varargs_1(int, nargs)
{
    va_list ap;
    register int i;
    Object arg1;

    SI_va_start(ap,nargs);
    Values_count = 0;
    if (!nargs)
	arg1 = NIL;
    else {
	arg1 = va_arg(ap, Object);
	Values_count++;
	for (i = 0; --nargs; i++) {
	    Values_count++;
	    Values[i] = va_arg(ap,Object);
	}
    }
    va_end(ap);
    return(arg1);
}
