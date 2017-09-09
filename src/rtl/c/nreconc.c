/*
 * nreconc.c -  Chestnut Run-Time Library entry for function nreconc
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object nreconc (x, y)
    Object x, y;
{
    Declare_local_temp;
    Object prev_cell = y, next_cell;

    while(TRUEP(x)) {
	next_cell = M_CDR(x);
	RPLACD(x, prev_cell);
	prev_cell = x;
	x = next_cell;
    }
    return VALUES_1(prev_cell);
}
