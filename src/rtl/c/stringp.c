/*
 * stringp.c -  Chestnut Run-Time Library entry for function stringp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object stringp (object)
    Object object;
{
    Declare_local_temp;
    return VALUES_1(STRINGP(object) ? T : NIL);
}
