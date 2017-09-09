/*
 * sublis.c -  Chestnut Run-Time Library entry for function sublis
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object assoc(Object item, Object a_list, Object test, Object test_not, Object key);
extern Object cons(Object,Object);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);

#else

extern Object assoc();
extern Object cons();
extern Object eql();
extern Object funcall1();

#endif


#include "lists.h"

Object sublis (alist, tree, test, test_not, key)
    Object alist, tree, test, test_not, key;
{
    Declare_local_temp;
    Object pair, a, d, result, treeitem;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(alist,tree,test,test_not,key);
    PROTECTI_4(pair,a,d,treeitem);

    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;

    if (TRUEP(pair = assoc(treeitem, alist, test, test_not, KOPT))) {
	result = M_CDR(pair);
    }
    else if (CONSP(tree)) {
	a = sublis(alist, M_CAR(tree), test, test_not, key);
	d = sublis(alist, M_CDR(tree), test, test_not, key);
	if (eql(a,M_CAR(tree)) && eql(d,M_CDR(tree)))
	    result = tree;
	else
	    result = cons(a,d);
    }
    else {
	result = tree;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
