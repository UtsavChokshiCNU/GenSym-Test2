/*
 * statclst.c -  Chestnut Run-Time Library entry for function STATIC_LIST
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;

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

Object STATIC_LIST varargs_1(int, n)
{
    Declare_local_temp;
    Object lastnode, newnode, result, *rest;
    long i;
    Declare_stack_pointer;
    Declare_area(a);

    if (n == 0)
	return VALUES_1(NIL);

    SAVE_STACK();
    SETUP_REST(n, rest);
    PROTECTI_3(lastnode, newnode, result);
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);
    result = NCONS(rest[0],lastnode);
    for (i = 1; i < n; ++i) {
	newnode = SI_cons();
	M_CDR(lastnode) = newnode;
	M_CAR(newnode) = rest[i];
	lastnode = newnode;
	M_CDR(lastnode) = NIL;
    }
    M_CDR(lastnode) = NIL;
    RESTORE_CURRENT_AREA(a);
    RESTORE_STACK();
    return VALUES_1(result);
}
