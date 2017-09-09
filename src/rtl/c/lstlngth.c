/*
 * lstlngth.c -  Chestnut Run-Time Library entry for function list_length
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object list_length (x)
    Object x;
{
    Declare_local_temp;
    long n = 0L;
    Object lfast = x;
    Object slow = x;
    Object temp1;

    while(TRUE) {
	if (ENDP(lfast)) {
	    temp1 = FIX(n);
	    break;
	}
	if (ENDP(M_CDR(lfast))) {
	    temp1 = FIX(n+1L);
	    break;
	}
	if (EQ(lfast,slow) && (n > 0L)) {
	    temp1 = NIL;
	    break;
	}
	n += 2L;
	lfast = CDDR(lfast);
	slow = CDR(slow);
    }
    return VALUES_1(temp1);
}
