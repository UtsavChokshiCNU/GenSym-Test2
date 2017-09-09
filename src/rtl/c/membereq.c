/*
 * membereq.c -  Chestnut Run-Time Library entry for function member_eq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object member_eq(item, list)
    Object item, list;
{
    Declare_local_temp;
    while (CONSP(list))
	if (item == M_CAR(list))
	    return VALUES_1(list);
        else
	    list = M_CDR(list);
    return VALUES_1(NIL);
}
