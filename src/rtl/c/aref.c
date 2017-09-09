/*
 * aref.c -  Chestnut Run-Time Library entry for function aref
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_array_row_major_index_aux(int n, va_list ap);
extern Object do_aref_1(Object arr, long i);

#else

extern Object SI_array_row_major_index_aux();
extern Object do_aref_1();

#endif




/* vararg version */
Object aref varargs_1(int, n)
{
    Object arr, result, i;
    va_list ap;

    SI_va_start(ap,n);
    arr = va_arg(ap,Object);
    if (n == 1L) i = ZERO;
    else if (n == 2L) i = va_arg(ap,Object);
    else {
	va_end(ap); SI_va_start(ap,n);
	i = SI_array_row_major_index_aux(n, ap);
    }
    result = do_aref_1(arr, IFIX(i));
    va_end(ap);
    return result;
}
