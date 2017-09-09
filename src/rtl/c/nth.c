/*
 * nth.c -  Chestnut Run-Time Library entry for function nth
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object nth(n, list)
    Object n, list;
{
    Declare_local_temp;
    long i;
    i = IFIX(n);
    while(i-- && TRUEP(list)) {
	list = M_CDR(list);
    }
    return VALUES_1(CAR(list));
}

Object nth_inline(n, list)
    Object n, list;
{
    Declare_local_temp;
    long i;
    i = IFIX(n);
    while(i-- && TRUEP(list)) {
	list = M_CDR(list);
    }
    return CAR(list);
}
