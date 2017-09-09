/*
 * nunion.c -  Chestnut Run-Time Library entry for function nunion
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object funcall1(Object func, Object arg);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);

#else

extern Object funcall1();
extern Object member();

#endif


#include "lists.h"

Object nunion (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object result = NIL, last_cdr = NIL, item = NIL;
    Declare_stack_pointer;

    if (UNSUPPLIED_P(key)) key = NIL;
    if (ENDP(list1))
	result = list2;
    else if (ENDP(list2))
	result = list1;
    else {
	SAVE_STACK();
	PROTECT_5(list1,list2,test,test_not,key);
	PROTECT_3(result,last_cdr,item);
	while (TRUEP(list1)) {
	    item = M_CAR(list1);
	    if (TRUEP(key))
		item = funcall1(key, item);
	    if (!TRUEP(member(item, list2, test, test_not, key))) {
		/* keep item, advance last_cdr */
		if (ENDP(result))
		    result = last_cdr = list1;
		else {
		    RPLACD(last_cdr,list1);
		    last_cdr = list1;
		}
	    }
	    list1 = M_CDR(list1);
	}
	if (TRUEP(result))
	    RPLACD(last_cdr,list2);
        else
	    result = list2;
	RESTORE_STACK();
    }
    return VALUES_1(result);
}
