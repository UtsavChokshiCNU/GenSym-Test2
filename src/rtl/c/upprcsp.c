/*
 * upprcsp.c -  Chestnut Run-Time Library entry for function upper_case_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#include "chars.h"

Object upper_case_p(c)
    Object c;
{
    Declare_local_temp;
    return VALUES_1(UPPER_CASE_P(c) ? T : NIL);
}
