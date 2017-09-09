/*
 * rwmjrrf.c -  Chestnut Run-Time Library entry for function row_major_aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_aref_1(Object arr, long i);

#else

extern Object do_aref_1();

#endif




Object row_major_aref (array, index)
    Object array, index;
{
    Declare_local_temp;
    return VALUES_1(ROW_MAJOR_AREF(array, index));
}
