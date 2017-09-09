/*
 * nsdffrnc.c -  Chestnut Run-Time Library entry for function nset_difference
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);

#else

extern Object cons();
extern Object funcall1();
extern Object member();

#endif


#include "lists.h"
   

Object nset_difference (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object result, last_cell, item1, elem, temp1;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(list1,list2,test,test_not,key);
    PROTECTI_5(result,last_cell,item1,elem,temp1);

    if (UNSUPPLIED_P(key)) key = NIL;
    result = last_cell = NIL;
    for (temp1 = list1; TRUEP(temp1); temp1 = M_CDR(temp1)) {
	item1 = elem = M_CAR(temp1);
	if (TRUEP(key))
	    item1 = funcall1(key, item1);
	if (!TRUEP(member(item1, list2, test, test_not, key))) {
	    if (ENDP(result)) {
	        result = last_cell = cons(elem, result);
	    }
	    else {
		RPLACD(last_cell, temp1);
		last_cell = temp1;
	    }
	}
    }
    if (TRUEP(last_cell))
	RPLACD(last_cell, NIL);
    RESTORE_STACK();
    return VALUES_1(result);
}
