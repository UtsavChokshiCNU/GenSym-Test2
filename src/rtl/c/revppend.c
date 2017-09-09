/*
 * revppend.c -  Chestnut Run-Time Library entry for function revappend
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object append2(Object list1, Object list2);
extern Object reverse(Object);

#else

extern Object append2();
extern Object reverse();

#endif


#include "lists.h"

Object revappend (x, y)
    Object x, y;
{
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    x = reverse(x);
    RESTORE_STACK();
    return(append2(x, y));
}
