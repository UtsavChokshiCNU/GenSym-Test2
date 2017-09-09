/*
 * assoc_eq.c -  Chestnut Run-Time Library entry for function assoc_eq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object assoc_eq (key, alist)
    Object key, alist;
{
    Declare_local_temp;
    Object elem;

    for ( ; CONSP(alist); alist = M_CDR(alist)) {
	elem = M_CAR(alist);
	if (CONSP(elem) && (M_CAR(elem) == key))
	    return VALUES_1(elem);
    }
    return VALUES_1(NIL);
}
