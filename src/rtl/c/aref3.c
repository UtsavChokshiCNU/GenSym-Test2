/*
 * aref3.c -  Chestnut Run-Time Library entry for function aref3
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




Object aref3 (arr, s1, s2, s3)
    Object arr;
    Object s1, s2, s3;
{
    return(do_aref_1(arr, (long)ROW_MAJOR_INDEX_3(arr, s1, s2, s3)));
}
