/*
 * smjndxx.c -  Chestnut Run-Time Library entry for function SI_array_row_major_index_aux
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_warn_fptr) ();

#endif




/* This function is used by aref, SETF_aref, and array_row_major_index_aux */

Object SI_array_row_major_index_aux (n, ap)
    long n;
    va_list ap;
{
    Declare_local_temp;
    SI_Dimension i, j;
    long rank;
    SI_Dimension *pdim;
    Object a;
    
    a = va_arg(ap,Object);
    if (SI_PRIMITIVE_VECTOR_P(a))
	return VALUES_1(va_arg(ap,Object));

    rank = SI_GENERAL_ARRAY_RANK(a);
    if (rank == 0)
	return VALUES_1(ZERO);
    j = IFIX(va_arg(ap,Object));
    if (rank == 1)
	return VALUES_1(FIX(j));
    pdim = &SI_GENERAL_NVARRAY_DIMENSION(a, 0);
    for (i = 1; i < rank ; ++i) {
	j *= *++pdim;
	j += IFIX(va_arg(ap,Object));
    }
    if (i < rank || --n != rank)
	warn(2, "array_row_major_index: inconsistent arguments - ~S ", a);
    return VALUES_1(FIX(j));
}
