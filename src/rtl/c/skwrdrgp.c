/*
 * skwrdrgp.c -  Chestnut Run-Time Library entry for function SI_keyword_arg_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/* Returns Fixnum indicating position of key value on stack
if key is found, NIL if not found */
/* I'm not entirely clear why this is a function, rather than part of
the expansion of KEYWORD_ARG(s); to save space at the expense of time,
I suppose */

Object SI_keyword_arg_p(key, args, n)
    Object key, *args;
    long n;
{
    long i;

    for(i=0; i < n; i += 2) {
	if (args[i] == key) {
	    return FIX(i+1);
	    /* NOTREACHED */
	}
    }
return NIL;
}
