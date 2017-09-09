/*
 * inspect.c -  Chestnut Run-Time Library entry for function inspect
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object describe(Object object);

#else

extern Object describe();

#endif




Object inspect (object)
    Object object;
{
    return (describe(object));
}
