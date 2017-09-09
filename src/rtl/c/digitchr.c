/*
 * digitchr.c -  Chestnut Run-Time Library entry for function digit_char
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "chars.h"

Object digit_char(weight, radix, font)
    Object weight, radix, font;
{
    Declare_local_temp;
    if (UNSUPPLIED_P(radix)) radix = FIX(10L);
    if (FIXNUM_MINUSP(weight) || FIXNUM_GE(weight, radix))
	return VALUES_1(NIL);
    if (FIXNUM_GE(weight, FIX(10L)))
	weight = FIXNUM_ADD(FIXNUM_MINUS(weight, FIX(10)), FIX('A'));
    else
	weight = FIXNUM_ADD(weight, FIX('0'));
    return VALUES_1(CODE_CHAR(weight));
}
