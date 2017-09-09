/*
 * char_lt.c -  Chestnut Run-Time Library entry for function char_lt
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "chars.h"

Object char_lt(a,b)
    Object a, b;
{
    Declare_local_temp;
    return VALUES_1(CHAR_LT(a,b) ? T : NIL);
}
