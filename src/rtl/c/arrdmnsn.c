/*
 * arrdmnsn.c -  Chestnut Run-Time Library entry for function array_dimension
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


Object array_dimension (arr, axis)
    Object arr;
    Object axis;
{
    Declare_local_temp;
    SI_Dimension result;
    if (SI_VECTOR_PRIMITIVE_P(arr))
	result = SI_PRIMITIVE_VECTOR_LENGTH(arr);
    else if (SI_GENERAL_ARRAY_RANK(arr) == 1)
	result = SI_GENERAL_VECTOR_TOTAL_SIZE(arr);
    else
	result = SI_GENERAL_NVARRAY_DIMENSION(arr, IFIX(axis));
    return VALUES_1(FIX(result));

}
