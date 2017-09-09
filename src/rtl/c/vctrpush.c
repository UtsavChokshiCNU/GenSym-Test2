/*
 * vctrpush.c -  Chestnut Run-Time Library entry for function vector_push
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object (*SI_error_fptr) ();
extern Object do_setf_aref();

#endif




Object vector_push (new_element, vector)
    Object new_element, vector;
{
    Declare_local_temp;
    Object fillptr;

    if (!ARRAY_HAS_FILL_POINTER_P(vector))
	return error(2, "vector_push: invalid argument - ~S", vector);

    fillptr = SI_GENERAL_VECTOR_FILL_POINTER(vector);
    if (FIXNUM_LT(fillptr, SI_GENERAL_VECTOR_TOTAL_SIZE(vector))) {
	(void)do_setf_aref(vector, (SI_Dimension)IFIX(fillptr), new_element);
	SET_FILL_POINTER(vector, FIXNUM_ADD1(fillptr));
	return VALUES_1(fillptr);
    }
    return VALUES_1(NIL);
}
