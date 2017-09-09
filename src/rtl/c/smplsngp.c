/*
 * smplsngp.c -  Chestnut Run-Time Library entry for function simple_string_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object simple_string_p (object)
    Object object;
{
    Declare_local_temp;
    return VALUES_1(SIMPLE_STRING_P(object) ? T : NIL);
}
