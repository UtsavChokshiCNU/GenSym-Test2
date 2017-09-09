/*
 * dbltntgr.c -  Chestnut Run-Time Library entry for function double_to_integer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern bignum_type double_to_bignum (double);

#else

extern bignum_type double_to_bignum ();

#endif



Object double_to_integer (d)
    double d;
{
    Object result;

#ifdef NEW_BIGNUMS
    /* Harbison and Steele say that a double to integer cast must truncate
       towards zero. */
    if (d > (double)(IMOST_NEGATIVE_FIXNUM - 1L) &&
	d < (double)(IMOST_POSITIVE_FIXNUM + 1L))
	result = FIX((SI_Long) d);
    else
	result = double_to_bignum(d);
#else
    result = T_MAKE_INTEGER((SI_Long) d);
#endif
    return result;
}
