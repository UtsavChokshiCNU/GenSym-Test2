/*
 * cp_alist.c -  Chestnut Run-Time Library entry for function cp_alist
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object ncons1(Object a);

#else

extern Object cons();
extern Object ncons1();

#endif


#include "lists.h"

/* enforsed entry name:  cp_alist (){} */

Object copy_alist (list)
    Object list;
{
    Declare_local_temp;
    Object result, last_cell, new_cell;
    Declare_stack_pointer;

    if (ENDP(list)) return VALUES_1(NIL);
    SAVE_STACK();
    PROTECT_1(list);
    PROTECTI_3(result,last_cell,new_cell);
    result = last_cell = ncons1(COPY_CONS(M_CAR(list)));
    list = M_CDR(list);
    while(CONSP(list)) {
	    new_cell = ncons1(COPY_CONS(M_CAR(list)));
	    RPLACD(last_cell, new_cell);
	    last_cell = new_cell;
	    list = M_CDR(list);
    }
    RPLACD(last_cell, list);
    RESTORE_STACK();
    return VALUES_1(result);
}
