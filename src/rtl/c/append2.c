/*
 * append2.c -  Chestnut Run-Time Library entry for function append2
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
extern Object copy_list(Object);

#else

extern Object SI_cons();
extern Object copy_list();

#endif


#include "lists.h"

#define NCONS1(a,result) (result=SI_cons(), \
                          M_CAR(result)=(a), \
                          M_CDR(result)=NIL, \
                          result)

Object append2 (list1, list2)
    Object list1, list2;
{
    Declare_local_temp;
    Object result, cell, temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(list1,list2);
    PROTECTI_3(result,cell,temp);
    
    if (ENDP(list1)) {
	result = list2;
    }
    else if (ENDP(list2)) {
#ifndef GCLISP
	result = copy_list(list1);
#else
	result = list1;
#endif
    }
    else {
	result = NCONS1(M_CAR(list1),cell);
	while (list1 = M_CDR(list1), !ENDP(list1)) {
	    NCONS1(M_CAR(list1),temp);
	    cell = (M_CDR(cell) = temp);
	}
	M_CDR(cell) = list2;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
