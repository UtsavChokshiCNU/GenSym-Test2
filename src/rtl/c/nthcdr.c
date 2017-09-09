/*
 * nthcdr.c -  Chestnut Run-Time Library entry for function nthcdr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object nthcdr(ln, list)
    Object ln, list;
{
    Declare_local_temp;
    long n;

    n = IFIX(ln);
    while(n-- && TRUEP(list)) {
	list = M_CDR(list);
    }
    return VALUES_1(list);
}
