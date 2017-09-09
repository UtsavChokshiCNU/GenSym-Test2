/*
 * tailp.c -  Chestnut Run-Time Library entry for function tailp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object tailp (sublist, list)
    Object sublist, list;
{
    Declare_local_temp;
    while (TRUEP(list)) {
	if (EQ(list, sublist))
	    return VALUES_1(T);
	list = M_CDR(list);
    }
    return VALUES_1(NIL);
}
