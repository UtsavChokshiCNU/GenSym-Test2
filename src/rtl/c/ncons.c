/*
 * ncons.c -  Chestnut Run-Time Library entry for function ncons
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;

#if SI_USE_PROTOTYPES

extern Object SI_cons(void);

#else

extern Object SI_cons();

#endif




Object ncons(a)
    Object a;
{
    Declare_local_temp;
    Object newnode;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(a);
    newnode = SI_cons();
    M_CAR(newnode) = a;
    M_CDR(newnode) = NIL;
    RESTORE_STACK();
    return VALUES_1(newnode);
}
