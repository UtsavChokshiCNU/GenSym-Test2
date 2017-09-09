/*
 * srwmjrrf.c -  Chestnut Run-Time Library entry for function set_row_major_aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object do_setf_aref();

#endif




Object set_row_major_aref (array, index, value)
    Object array, index, value;
{
    Declare_local_temp;
    (void)SET_ROW_MAJOR_AREF(array, index, value);
    return VALUES_1( value);
}
