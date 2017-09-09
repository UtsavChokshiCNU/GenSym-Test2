/*
 * amjndx.c -  Chestnut Run-Time Library entry for function array_row_major_index
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_array_row_major_index_aux(int n, va_list ap);

#else

extern Object SI_array_row_major_index_aux();

#endif




Object array_row_major_index varargs_1(int, n)
{
    Object res;
    va_list ap;
    SI_va_start(ap,n);
    res = SI_array_row_major_index_aux(n, ap);
    va_end(ap);
    return res;
}
