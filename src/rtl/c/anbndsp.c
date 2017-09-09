/*
 * anbndsp.c -  Chestnut Run-Time Library entry for function array_in_bounds_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

 
Object array_in_bounds_p varargs_1(int, n)
{
    Declare_local_temp;
    Object arr;
    SI_Long sub;
    SI_Dimension *pdim;
    long rank, i;
    va_list ap;

    SI_va_start(ap,n);
    arr = va_arg(ap, Object);
    --n;
    if (SI_PRIMITIVE_VECTOR_P(arr)) {
	/* if (n != 1) error? */
	sub = IFIX(va_arg(ap, Object));
	if ((sub < 0) || (sub >= SI_PRIMITIVE_VECTOR_LENGTH(arr)))
	    return VALUES_1(NIL);
    }
    else {
	rank = SI_GENERAL_ARRAY_RANK(arr);
	if (rank == 1L) {
	    sub = IFIX(va_arg(ap, Object));
	    if ((sub < 0) || (sub >= SI_GENERAL_VECTOR_TOTAL_SIZE(arr)))
		return VALUES_1(NIL);
	} else {
	    pdim = &SI_GENERAL_NVARRAY_DIMENSION(arr, 0);
	    for (i = 0; i < rank; ++i) {
		sub = IFIX(va_arg(ap,Object));
		if (sub < 0 || sub >= *pdim++)
		    return VALUES_1(NIL);
	    }
        }
    }
    va_end(ap);
    return VALUES_1(T);
}
