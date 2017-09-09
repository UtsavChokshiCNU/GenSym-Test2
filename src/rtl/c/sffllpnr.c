/*
 * sffllpnr.c -  Chestnut Run-Time Library entry for function setf_fill_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object setf_fill_pointer(arr, fillptr)
    Object arr, fillptr;
{
    Declare_local_temp;
    SET_FILL_POINTER(arr, fillptr);
    return VALUES_1(fillptr);
}
