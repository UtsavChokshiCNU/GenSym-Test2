/*
 * apply3.c -  Chestnut Run-Time Library entry for function apply3
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);

#else

extern Object SI_internal_funcall();

#endif




Object apply3 (func, arg1, arg2, arglist)
    Object func, arg1, arg2, arglist;
{
    STACK_PUSH(arg1);
    STACK_PUSH(arg2);
    return SI_internal_funcall(func, 2, arglist);
}
