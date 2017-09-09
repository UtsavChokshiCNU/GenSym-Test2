/*
 * subst.c -  Chestnut Run-Time Library entry for function subst
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
extern Object cons(Object,Object);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);

#else

extern Object STATIC_FUNCTION1();
extern Object cons();
extern Object eql();
extern Object funcall1();
extern Object funcall2();

#endif


#include "lists.h"

Object subst (new, old, tree, test, test_not, key)
    Object new, old, tree, test, test_not, key;
{
    Declare_local_temp;
    Object a, d, temp1, treeitem, treecar, treecdr;
    long testp = !UNSUPPLIED_P(test);
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_6(new,old,tree,test,test_not,key);
    PROTECTI_6(a,d,temp1,treeitem,treecar,treecdr);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }
    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;
    if (SATISFIESP(testp, test, test_not, old, treeitem)) 
	temp1 = new;
    else if (ATOM(tree))
	temp1 = tree;
    else {
	a = subst(new,old,M_CAR(tree),test,test_not,key);
	d = subst(new,old,M_CDR(tree),test,test_not,key);
	if (EQL(a, M_CAR(tree)) && EQL(d, M_CDR(tree)))
	    temp1 = tree;
	else
	    temp1 = cons(a,d);
    }
    RESTORE_STACK();
    return VALUES_1(temp1);
}
