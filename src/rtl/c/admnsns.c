/*
 * admnsns.c -  Chestnut Run-Time Library entry for function array_dimensions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);

#else

extern Object cons();

#endif




Object array_dimensions (arr)
    Object arr;
{
    Declare_local_temp;
    Object result = NIL;
    Object dimensions = NIL;
    SI_Dimension rank;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(result, dimensions);
    if (SI_PRIMITIVE_VECTOR_P(arr))
	result = cons(FIX(SI_PRIMITIVE_VECTOR_LENGTH(arr)), NIL);
    else {
	rank = SI_GENERAL_ARRAY_RANK(arr);
	if (rank == 1)
	    result = cons(FIX(SI_GENERAL_VECTOR_TOTAL_SIZE(arr)), NIL);
	else {
	    dimensions = SI_GENERAL_NVARRAY_DIMENSIONS(arr);
	    while (rank--)
		result = cons(FIX(SI_PRIMITIVE_VECTOR_CONTENTS(dimensions,
							       SI_PVT_Dimension)
				  [rank]),
			      result);
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);  /* gets pushed in reverse so ends up forward */
}
