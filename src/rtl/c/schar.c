/*
 * schar.c -  Chestnut Run-Time Library entry for function schar
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object schar (str, index)
    Object str;
    Object index;
{
    Declare_local_temp;
    Object result;

    result = SCHAR(str, index);
    return VALUES_1(result);
}
