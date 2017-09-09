/*
 * asllpnp.c -  Chestnut Run-Time Library entry for function array_has_fill_pointer_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object array_has_fill_pointer_p (arr)
    Object arr;
{
    Declare_local_temp;
    return VALUES_1(ARRAY_HAS_FILL_POINTER_P(arr) ? T : NIL);
}
