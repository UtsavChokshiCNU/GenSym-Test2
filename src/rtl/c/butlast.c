/*
 * butlast.c -  Chestnut Run-Time Library entry for function butlast
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern long ilength(Object sequence);
extern Object ncons1(Object a);

#else

extern long ilength();
extern Object ncons1();

#endif


#include "lists.h"

/* &optional 1 1 */
Object butlast (list, optn)
    Object list, optn;
{
    Declare_local_temp;
    long i, n, len = ilength(list);
    Object result, last_cell, new_cell;
    Declare_stack_pointer;

    n = UNSUPPLIED_P(optn) ? 1L : IFIX(optn);
    if (n >= len)
	return VALUES_1(NIL);
    SAVE_STACK();
    PROTECT_1(list);
    PROTECTI_3(result,last_cell,new_cell);
    result = last_cell = ncons1(M_CAR(list));
    list = M_CDR(list);
    for (i = 1L; CONSP(list) && (i < (len - n)); i++) {
	new_cell = ncons1(M_CAR(list));
	RPLACD(last_cell, new_cell);
	last_cell = new_cell;
	list = M_CDR(list);
    }
    RPLACD(last_cell, NIL);
    RESTORE_STACK();
    return VALUES_1(result);
}
