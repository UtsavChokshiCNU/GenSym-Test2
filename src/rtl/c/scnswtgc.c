/*
 * scnswtgc.c -  Chestnut Run-Time Library entry for function SI_cons_with_gc
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



#if  SI_QUICK_CONS

Object SI_cons_with_gc (x,y)
    Object x, y;
{
    Declare_local_temp;
    Object newnode;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    
    newnode =  SI_cons();
    M_CAR(newnode) = x;
    M_CDR(newnode) = y;
    RESTORE_STACK();
    return VALUES_1(newnode);
}

/* Procedure version of CONS macro --- why does this exist? */
Object cons (x,y)
    Object x, y;
{
    Declare_local_temp;
    Object newnode;

    newnode = CONS(x,y);
    return VALUES_1(newnode);
}

#else

Object cons (x,y)
    Object x, y;
{
    Declare_local_temp;
    Object newnode;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(x,y);
    
    newnode =  SI_cons();
    M_CAR(newnode) = x;
    M_CDR(newnode) = y;
    RESTORE_STACK();
    return VALUES_1(newnode);
}

#endif /* SI_QUICK_CONS */

