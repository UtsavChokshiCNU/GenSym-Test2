/*
 * chrcter.c -  Chestnut Run-Time Library entry for function character
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qcharacter;

#if SI_USE_PROTOTYPES

extern Object coerce(Object,Object);

#else

extern Object coerce();

#endif


#include "chars.h"

Object character(x)
    Object x;
{
    return coerce(x, Qcharacter);
}
