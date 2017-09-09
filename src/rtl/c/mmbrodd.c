/*
 * mmbrodd.c -  Chestnut Run-Time Library entry for function member_odd
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

/* member-odd is an extension to support DEFKEY in GCLISP */
Object member_odd (v,l)
    Object v;
    Object l;
{
    Declare_local_temp;
    Object tail;
    Object temp1;

    for (tail = l; !ENDP(tail); tail = CDDR(tail)) 
	if (EQ(v,CAR(tail))) {
	    temp1 = tail;
	    goto LABEL1;
	}
    temp1 = NIL;
    LABEL1: 
    return VALUES_1(temp1);
}
