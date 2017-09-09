/*
 * chrlsspr.c -  Chestnut Run-Time Library entry for function char_lesspr
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object char_lesspn(long,...);

#else

extern Object char_lesspn();

#endif

typedef Object (*FUN_T) (Object, Object);
#include "chars.h"

Object char_lesspr(a,b)
    Object	a, b;
{
    return SI_char_relop((FUN_T)char_lesspn, a, b);
}
