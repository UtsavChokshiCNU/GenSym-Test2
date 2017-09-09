/*
 * adjoin.c -  Chestnut Run-Time Library entry for function adjoin
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

Object adjoin (item, list, test, test_not, key)
    Object item, list, test, test_not, key;
{
    Declare_local_temp;
    Object keyitem, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(item,list,test,test_not,key);
    PROTECTI_1(keyitem);
    if (UNSUPPLIED_P(key)) key = NIL;
    keyitem = TRUEP(key) ? funcall1(key, item) : item;
    if (TRUEP(member(keyitem, list, test, test_not, key))) {
	RESTORE_STACK();
	return VALUES_1(list);
    }
    result = cons(item, list);
    RESTORE_STACK();
    return VALUES_1(result);
}
