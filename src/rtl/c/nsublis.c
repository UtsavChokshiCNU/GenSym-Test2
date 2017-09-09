/*
 * nsublis.c -  Chestnut Run-Time Library entry for function nsublis
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object assoc(Object item, Object a_list, Object test, Object test_not, Object key);
extern Object funcall1(Object func, Object arg);

#else

extern Object assoc();
extern Object funcall1();

#endif


#include "lists.h"

Object nsublis (alist, tree, test, test_not, key)
    Object alist, tree, test, test_not, key;
{
    Declare_local_temp;
    Object pair, treeitem;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(alist,tree,test,test_not,key);
    PROTECTI_2(pair, treeitem);

    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;

    if (TRUEP(pair = assoc(treeitem,alist,test, test_not, KOPT))) {
	RESTORE_STACK();
	return VALUES_1(M_CDR(pair));
    }
    if (CONSP(tree)) {
	/* replacX should not evaluate consing 2-nd argument */
	pair = nsublis(alist, M_CAR(tree), test, test_not, key);
	RPLACA(tree, pair);
	pair = nsublis(alist, M_CDR(tree), test, test_not, key);
	RPLACD(tree, pair);
    }
    RESTORE_STACK();
    return VALUES_1(tree);
}
