/*
 * ldiff.c -  Chestnut Run-Time Library entry for function ldiff
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object ncons1(Object a);

#else

extern Object ncons1();

#endif


#include "lists.h"

Object ldiff (list, sublist)		/* ; replaces my version */
    Object list, sublist;
{
    Declare_local_temp;
    Object result = NIL, last_cell = NIL, new_cell, temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(list,sublist,result,last_cell);
    PROTECTI_2(new_cell,temp);
    while (CONSP(list)) {
	if (EQ(list, sublist))
	    break;
	new_cell = ncons1(M_CAR(list));
	if (ENDP(result)) {
	    result = last_cell = new_cell;
	}
	else {
	    RPLACD(last_cell, new_cell);
	    last_cell = new_cell;
	}
	list = M_CDR(list);
    }
    if (TRUEP(last_cell))
	RPLACD(last_cell, NIL);
    RESTORE_STACK();
    return VALUES_1(result);
}
