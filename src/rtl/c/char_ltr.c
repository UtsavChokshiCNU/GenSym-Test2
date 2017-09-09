/*
 * char_ltr.c -  Chestnut Run-Time Library entry for function char_ltr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object char_lt(Object a, Object b);

#else

extern Object char_lt();

#endif


#include "chars.h"

Object char_ltr(a,b)
    Object	a, b;
{
    return SI_char_relop(char_lt, a, b);
}
