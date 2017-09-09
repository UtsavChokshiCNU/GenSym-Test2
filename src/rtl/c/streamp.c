/*
 * streamp.c -  Chestnut Run-Time Library entry for function streamp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object streamp (stream)
    Object stream;
{
    Declare_local_temp;
    return VALUES_1(STREAMP(stream) ? T : NIL);
}
