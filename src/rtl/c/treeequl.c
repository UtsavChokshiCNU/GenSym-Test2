/*
 * treeequl.c -  Chestnut Run-Time Library entry for function tree_equal
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
extern Object funcall2(Object func, Object arg1, Object arg2);

#else

extern Object STATIC_FUNCTION1();
extern Object eql();
extern Object funcall2();

#endif


#include "lists.h"

Object tree_equal (x, y, test, test_not)
    Object x, y, test, test_not;
{
    Declare_local_temp;
    Object temp1, temp2, result;
    int testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(x,y,test,test_not);
    PROTECTI_3(temp1,temp2,result);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    if (ATOM(x) && ATOM(y)) {
	if (!SATISFIESP(testp, test, test_not, x, y)) 
	    result = NIL;
	else
	    result = T;
    }
    else if (ATOM(x) || ATOM(y))
	result = NIL;
    else {
        for (temp1 = x, temp2 = y; CONSP(temp1) && CONSP(temp2);
	     temp1 = M_CDR(temp1), temp2=M_CDR(temp2)) {
	    if (!TRUEP(tree_equal(M_CAR(temp1), M_CAR(temp2), test, test_not)))
		result = NIL;
        }
	if (TRUEP(temp1) || TRUEP(temp2))
	    result = tree_equal(temp1,temp2,test,test_not);
	else
	    result = T;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
