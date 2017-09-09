/*
 * ttlmmrsd.c -  Chestnut Run-Time Library entry for function total_memory_used
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kdynamic;
extern Object Kstatic;

#if SI_USE_PROTOTYPES

extern Object add(Object a, Object b);
extern Object area_memory_used(Object);

#else

extern Object add();
extern Object area_memory_used();

#endif




Object total_memory_used()
{
    Object temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECTI_1(temp1);
    temp1 = add(area_memory_used(Kstatic), area_memory_used(Kdynamic));
    RESTORE_STACK();
    return(temp1);
}
