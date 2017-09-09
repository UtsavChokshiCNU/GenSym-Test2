/*
 * fllpntr.c -  Chestnut Run-Time Library entry for function fill_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object fill_pointer (vector)
    Object vector;
{
    Declare_local_temp;
    return VALUES_1(SI_GENERAL_VECTOR_FILL_POINTER(vector));
}
