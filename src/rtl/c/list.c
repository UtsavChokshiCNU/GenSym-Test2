/*
 * list.c -  Chestnut Run-Time Library entry for function list
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


#include "lists.h"

#define NCONS(a,result) (result=SI_cons(), \
                         M_CAR(result)=(a), \
                         M_CDR(result)=NIL, \
                         result)

Object list varargs_1(int, n)
{
    Declare_local_temp;
    Object lastnode, newnode, result, *rest;
    long i;
    Declare_stack_pointer;

    if (n == 0)
	return VALUES_1(NIL);

    SAVE_STACK();
    SETUP_REST(n, rest);
    PROTECTI_3(lastnode, newnode, result);

    result = NCONS(rest[0],lastnode);
    for (i = 1; i < n; ++i) {
	newnode = SI_cons();
	M_CDR(lastnode) = newnode;
	M_CAR(newnode) = rest[i];
	lastnode = newnode;
	M_CDR(lastnode) = NIL;
    }
    M_CDR(lastnode) = NIL;
    RESTORE_STACK();
    return VALUES_1(result);
}
