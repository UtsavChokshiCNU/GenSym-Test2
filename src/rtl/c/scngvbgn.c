/*
 * scngvbgn.c -  Chestnut Run-Time Library entry for function STATIC_NEGATIVE_BIGNUM
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object SI_alloc_bignum(SI_Dimension length);

#else

extern Object SI_alloc_bignum();

#endif




Object STATIC_NEGATIVE_BIGNUM (length)
    SI_Dimension length;
{
    Object result;
    Declare_area(a);

    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = BIGNUM_ALLOCATE(length);
    BIGNUM_SET_HEADER(result, length, TRUE);
    RESTORE_CURRENT_AREA(a);

    return result;
}
