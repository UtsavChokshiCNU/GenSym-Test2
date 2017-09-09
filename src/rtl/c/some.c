/*
 * some.c -  Chestnut Run-Time Library entry for function some
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);
extern Object do_aref_1(Object arr, long i);
extern long ilength(Object sequence);

#else

extern Object SI_internal_funcall();
extern Object do_aref_1();
extern long ilength();

#endif


#include "some.h"

Object some varargs_1(int, n)
{
    INVOKE_SEVERAL(SOME_FUNC,1,n);
}

Object every varargs_1(int, n)
{
    INVOKE_SEVERAL(EVERY_FUNC,1,n);
}

Object notany varargs_1(int, n)
{
    INVOKE_SEVERAL(SOME_FUNC,0,n);
}


Object notevery varargs_1(int, n)
{
    INVOKE_SEVERAL(EVERY_FUNC,0,n);
}

