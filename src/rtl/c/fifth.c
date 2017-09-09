/*
 * fifth.c -  Chestnut Run-Time Library entry for function fifth
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object nth_inline(Object,Object);

#else

extern Object nth_inline();

#endif


#include "lists.h"

Object fifth (list)
    Object list;
{
    Declare_local_temp;
    return (Object)VALUES_1(FIFTH(list));
}
