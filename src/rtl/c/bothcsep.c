/*
 * bothcsep.c -  Chestnut Run-Time Library entry for function both_case_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#include "chars.h"

Object both_case_p(c)
    Object c;
{
    Declare_local_temp;
    long code = ICHAR_CODE(c);

    return VALUES_1(((isupper(code) && islower(TOLOWER(code))) ||
	    (islower(code) && isupper(TOUPPER(code)))) ? T : NIL);
}
