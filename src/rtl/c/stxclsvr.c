/*
 * stxclsvr.c -  Chestnut Run-Time Library entry for function set_exclusive_or
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
extern Object reverse(Object);

#else

extern Object cons();
extern Object funcall1();
extern Object member();
extern Object reverse();

#endif


#include "lists.h"

Object set_exclusive_or (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object result, item, temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(list1,list2,test,test_not,key);
    PROTECTI_3(result,item,temp);

    if (UNSUPPLIED_P(key)) key = NIL;
    result = NIL;
    list2 = reverse(list2);  /* for Lucid compatibility, preserve order */
    for (temp = list2; TRUEP(temp); temp = M_CDR(temp)) {
	item = M_CAR(temp);
	if (TRUEP(key))
	    item = funcall1(key, item);
	if (!TRUEP(member(item, list1, test, test_not, key)))
	    result = cons(M_CAR(temp), result);
    }

    list1 = reverse(list1);  /* for Lucid compatibility, preserve order */
    for (temp = list1; TRUEP(temp); temp = M_CDR(temp)) {
	item = M_CAR(temp);
	if (TRUEP(key))
	    item = funcall1(key, item);
	if (!TRUEP(member(item, list2, test, test_not, key)))
	    result = cons(M_CAR(temp), result);
    }

    RESTORE_STACK();
    return VALUES_1(result);
}
