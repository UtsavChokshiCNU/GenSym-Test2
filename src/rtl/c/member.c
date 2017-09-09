/*
 * member.c -  Chestnut Run-Time Library entry for function member
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_fp_eql_1;

#if SI_USE_PROTOTYPES

extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);

#else

extern Object STATIC_FUNCTION1();
extern Object eql();
extern Object funcall1();
extern Object funcall2();

#endif


#include "lists.h"

Object member (item, list, test, test_not, key)
    Object item, list, test, test_not, key;
{
    Declare_local_temp;
    Object elemkey;
    long testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(item,list,test,test_not,key);
    PROTECTI_1(elemkey);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }
    if (UNSUPPLIED_P(key)) key = NIL;
    while (!ENDP(list)) {
	elemkey = M_CAR(list);
	if (TRUEP(key))
	    elemkey = funcall1(key, elemkey);
	if (SATISFIESP(testp, test, test_not, item, elemkey)) {
	    RESTORE_STACK();
	    return VALUES_1(list);
	}
	list = M_CDR(list);
    }
    RESTORE_STACK();
    return VALUES_1(NIL);
}
