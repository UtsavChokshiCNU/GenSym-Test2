/*
 * copylist.c -  Chestnut Run-Time Library entry for function copy_list
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

#define NCONS1(a,result) (result=SI_cons(), \
                          M_CAR(result)=(a), \
                          M_CDR(result)=NIL, \
                          result)

Object copy_list (list)
    Object list;
{
    Declare_local_temp;
    Object result, last_cell, new_cell;
    Declare_stack_pointer;

    if (ENDP(list)) return VALUES_1(NIL);
    SAVE_STACK();
    PROTECT_1(list);
    PROTECTI_3(result,last_cell,new_cell);

    result = NCONS1(M_CAR(list),last_cell);
    list = M_CDR(list);
    /* Residual quasifeature: don't really need to keep last cdr. */
    while(CONSP(list)) {
	    NCONS1(M_CAR(list),new_cell);
	    RPLACD(last_cell, new_cell);
	    last_cell = new_cell;
	    list = M_CDR(list);
    }
    RPLACD(last_cell, list);
    RESTORE_STACK();
    return VALUES_1(result);
}
