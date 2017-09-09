/*
 * nsubst.c -  Chestnut Run-Time Library entry for function nsubst
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

Object nsubst (new, old, tree, test, test_not, key)
    Object new, old, tree, test, test_not, key;
{
    Declare_local_temp;
    Object treeitem;
    long testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_6(new,old,tree,test,test_not,key);
    PROTECTI_1(treeitem);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    /* if key passed, only apply to tree, not passed to test function */
    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;
    if (SATISFIESP(testp, test, test_not, old, treeitem)) {
	RESTORE_STACK();
	return VALUES_1(new);
    }
    if (CONSP(tree)) {
	/* replacX should not evaluate consing 2-nd argument */
	treeitem =  nsubst(new, old, M_CAR(tree), test, test_not, key);
	RPLACA(tree, treeitem);
	treeitem =  nsubst(new, old, M_CDR(tree), test, test_not, key);
	RPLACD(tree, treeitem);
    }
    RESTORE_STACK();
    return VALUES_1(tree);
}
