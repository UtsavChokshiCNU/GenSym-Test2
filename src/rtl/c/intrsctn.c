/*
 * intrsctn.c -  Chestnut Run-Time Library entry for function intersection
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

Object intersection (list1, list2, test, test_not, key)
    Object list1, list2, test, test_not, key;
{
    Declare_local_temp;
    Object result, item1, temp1, elem;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(list1,list2,test,test_not,key);
    PROTECTI_4(result,item1,temp1,elem);
    if (UNSUPPLIED_P(key)) key = NIL;
    result = NIL;
    list1 = reverse(list1);  /* for Lucid compatibility, preserve order */
    for (temp1 = list1; TRUEP(temp1); temp1 = M_CDR(temp1)) {
	item1 = elem = M_CAR(temp1);
	if (TRUEP(key))
	    item1 = funcall1(key, item1);
	if (TRUEP(member(item1, list2, test, test_not, key)))
	    result = cons(elem, result);
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
