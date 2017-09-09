/*
 * statlsts.c -  Chestnut Run-Time Library entry for function STATIC_LIST_STAR
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

extern Object ncons(Object a);

#else

extern Object ncons();

#endif


#include "lists.h"


Object STATIC_LIST_STAR varargs_1(int, n)
{
    Declare_local_temp;
    Object result, next, last_cell, new_last_cell, *rest;
    int i;
    Declare_stack_pointer;
    Declare_area(a);

    SAVE_STACK();
    SETUP_REST(n, rest);
    PROTECTI_4(result, next, last_cell, new_last_cell);

    next = rest[0];
    if (!(--n))
	result = next;
    else {
        SAVE_CURRENT_AREA(a);
	SET_CURRENT_AREA(Static_area);
	result = last_cell = ncons(next);
	for (i = 1; i < n; ++i) {
	    next = rest[i];
	    new_last_cell = ncons(next);
	    RPLACD(last_cell, new_last_cell);
	    last_cell = new_last_cell;
	}
	next = rest[n];
	RPLACD(last_cell,next);
	RESTORE_CURRENT_AREA(a);
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
