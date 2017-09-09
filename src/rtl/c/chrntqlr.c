/*
 * chrntqlr.c -  Chestnut Run-Time Library entry for function char_not_equalr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object char_not_equal(Object a, Object b);

#else

extern Object char_not_equal();

#endif


#include "chars.h"

Object char_not_equalr(a,b)
    Object	a, b;
{
    return SI_char_relop(char_not_equal, a, b);
}
