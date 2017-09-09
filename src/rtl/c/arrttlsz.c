/*
 * arrttlsz.c -  Chestnut Run-Time Library entry for function array_total_size
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object array_total_size (arr)
    Object arr;
{
    Declare_local_temp;
    SI_Dimension *pdim;
    long rank;
    SI_Dimension size;

    if (SI_PRIMITIVE_VECTOR_P(arr)) {
	size = SI_PRIMITIVE_VECTOR_LENGTH(arr);
	return VALUES_1(FIX(size));
    } else {
	rank = SI_GENERAL_ARRAY_RANK(arr);
	if (rank == 1L)
	    return VALUES_1(FIX(SI_GENERAL_VECTOR_TOTAL_SIZE(arr)));
	else {
	    pdim = &SI_GENERAL_NVARRAY_DIMENSION(arr, 0);
	    size = 1L;
	    while (rank--)
		size *= *pdim++;
	    return VALUES_1(FIX(size));
	}
    }
}
