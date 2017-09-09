/*
 * dgtchrp.c -  Chestnut Run-Time Library entry for function digit_char_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "chars.h"

Object digit_char_p(c, rad)
    Object c;  /* character */
    Object rad;  /* radix */
{
    Declare_local_temp;
    long code = ICHAR_CODE(c);
    long r;

    r = UNSUPPLIED_P(rad) ? 10 : (UCHAR) IFIX(rad);
    if (code >= '0' && code <= '9')
	code -= '0';
    else if (code >= 'A' && code <= 'Z')
	code = (code - 'A') + 10;
    else if (code >= 'a' && code <= 'z')
	code = (code - 'a') + 10;
    else
	return VALUES_1(NIL);
    return VALUES_1((code < r) ? FIX(code) : NIL);
}
