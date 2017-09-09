/*
 * hsnmsrng.c -  Chestnut Run-Time Library entry for function host_namestring
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "filesys.h"

Object host_namestring (pathnm)
    Object pathnm;
{
    Declare_local_temp;
    return VALUES_1(NIL);
}
