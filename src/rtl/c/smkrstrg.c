/*
 * smkrstrg.c -  Chestnut Run-Time Library entry for function SI_make_rest_arg
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);

#else

extern Object cons();

#endif




Object SI_make_rest_arg (args, n)
    Object *args;
    long n;
{
    Object value = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(value);

    while (n-- > 0) value = cons(args[n], value);

    RESTORE_STACK();
    return value;
}
