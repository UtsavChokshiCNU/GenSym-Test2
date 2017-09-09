/*
 * acons.c -  Chestnut Run-Time Library entry for function acons
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


#include "lists.h"

Object acons (key, datum, a_list)
    Object key, datum, a_list;
{
    Declare_local_temp;
    Object result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(key,datum,a_list);
    result = cons(cons(key,datum),a_list);
    RESTORE_STACK();
    return VALUES_1(result);
}
