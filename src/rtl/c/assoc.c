/*
 * assoc.c -  Chestnut Run-Time Library entry for function assoc
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

Object assoc (item, a_list, test, test_not, key)
    Object item, a_list, test, test_not, key;
{
    Declare_local_temp;
    Object elem, elemkey;
    long testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(item,a_list,test,test_not,key);
    PROTECTI_2(elem,elemkey);

    if (UNSUPPLIED_P(key)) key = NIL;
    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    while(CONSP(a_list)) {
	elem = M_CAR(a_list);
	if (CONSP(elem)) {
	    /* Skip NIL alist entries; else perform test */
	    elemkey = M_CAR(elem);
	    if (TRUEP(key))
	        elemkey = funcall1(key, elemkey);

	    if (SATISFIESP(testp, test, test_not, item, elemkey)) {
		RESTORE_STACK();
		return VALUES_1(elem);
	    }
	}
	a_list = M_CDR(a_list);
    }
    RESTORE_STACK();
    return VALUES_1(NIL);
}
