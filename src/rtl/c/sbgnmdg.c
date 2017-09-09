/*
 * sbgnmdg.c -  Chestnut Run-Time Library entry for function SET_BIGNUM_DIGIT
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


void SET_BIGNUM_DIGIT(bignum, number, high, low)
    Object bignum;
    SI_Dimension number;
    SI_Long high, low;
{
    SI_Bignum_digit_type *start;
    start = BIGNUM_START_PTR(bignum);
    start[number] = (SI_Bignum_digit_type) ((high << 15) | low);
}
