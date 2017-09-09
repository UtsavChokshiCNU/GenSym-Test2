/*
 * subsetp.c -  Chestnut Run-Time Library entry for function subsetp
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

Object subsetp (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object item, temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(list1,list2,test,test_not,key);
    PROTECTI_2(item,temp);

    if (UNSUPPLIED_P(key)) key = NIL;
    for (temp = list1; TRUEP(temp); temp = M_CDR(temp)) {
	item = M_CAR(temp);
	if (TRUEP(key))
	    item = funcall1(key, item);
	if (!TRUEP(member(item, list2, test, test_not, key))) {
	    RESTORE_STACK();
	    return VALUES_1(NIL);
	}
    }
    RESTORE_STACK();
    return VALUES_1(T);
}
