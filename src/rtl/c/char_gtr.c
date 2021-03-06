/*
 * char_gtr.c -  Chestnut Run-Time Library entry for function char_gtr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object char_gt(Object a, Object b);

#else

extern Object char_gt();

#endif


#include "chars.h"

Object char_gtr(a,b)
    Object	a, b;
{
    return SI_char_relop(char_gt, a, b);
}
