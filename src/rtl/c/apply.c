/*
 * apply.c -  Chestnut Run-Time Library entry for function apply
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




Object apply varargs_1(int, n)
{
    long i;
    Object *sp;
    va_list ap;
    Object func, arglist;

    SI_va_start(ap,n);
    func = va_arg(ap, Object);
    n -= 2;

    sp = (Object *)Stack;
    Stack += n;
    for(i = 0; i < n; ++i)
	*sp++ = va_arg(ap, Object);
    arglist = va_arg(ap, Object);
    va_end(ap);

    return SI_internal_funcall(func, n, arglist);
}
