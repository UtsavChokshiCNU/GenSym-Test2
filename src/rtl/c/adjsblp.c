/*
 * adjsblp.c -  Chestnut Run-Time Library entry for function adjustable_array_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object adjustable_array_p (arr)
    Object arr;
{
    Declare_local_temp;
    return VALUES_1(ADJUSTABLE_ARRAY_P(arr) ? T : NIL);
}
