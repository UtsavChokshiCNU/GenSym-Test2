/*
 * setfaref.c -  Chestnut Run-Time Library entry for function SETF_aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_array_row_major_index_aux(long n, va_list ap);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object SI_array_row_major_index_aux();
extern Object do_setf_aref();

#endif




#if SI_SUPPORT_SF
/* vararg version */
Object SETF_aref varargs_1(int, n)
{
    Object new, arr, result, i;
    va_list ap, saveap;

    SI_va_start(ap,n);
    SI_va_start(saveap,n);
    new = va_arg(ap,Object);
    arr = va_arg(ap,Object);
    if (n == 2) i = ZERO;
    else if (n == 3) i = va_arg(ap,Object);
    else {
	va_arg(saveap, Object);
	i = SI_array_row_major_index_aux(n-1, saveap);
    }
    result = do_setf_aref(arr, (SI_Dimension)IFIX(i), new);
    va_end(ap);
    va_end(saveap);
    return result;
}
#endif
