/*
 * aref7.c -  Chestnut Run-Time Library entry for function aref7
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_aref_1(Object arr, long i);

#else

extern Object do_aref_1();

#endif




Object aref7 (arr, s1, s2, s3, s4, s5, s6, s7)
    Object arr;
    Object s1, s2, s3, s4, s5, s6, s7;
{
    return(do_aref_1(arr, (long)ROW_MAJOR_INDEX_7(arr, s1, s2, s3, s4,
						  s5, s6, s7)));
}
