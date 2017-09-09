/*
 * vctorpop.c -  Chestnut Run-Time Library entry for function vector_pop
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object aref1(Object arr, Object s1);

#else

extern Object (*SI_error_fptr) ();
extern Object aref1();

#endif




Object vector_pop (vector)
    Object vector;
{
    Object fillptr;

    if (!ARRAY_HAS_FILL_POINTER_P(vector))
	return error(2, "vector_pop: invalid argument - ~S", vector);
    fillptr = SI_GENERAL_VECTOR_FILL_POINTER(vector);
    SET_FILL_POINTER(vector, FIXNUM_SUB1(fillptr));
    return aref1(vector, fillptr);
}
