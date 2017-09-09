/*
 * subst_if.c -  Chestnut Run-Time Library entry for function subst_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);

#else

extern Object cons();
extern Object eql();
extern Object funcall1();

#endif


#include "lists.h"

Object subst_if (new, test, tree, key)
    Object new, test, tree, key;
{
    Declare_local_temp;
    Object a, d, temp1, treecar, treecdr, treeitem;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(new,test,tree,key);
    PROTECTI_6(a,d,temp1,treecar, treecdr, treeitem);

    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;
    if (funcall1(test, treeitem))
	temp1 = new;
    else if (ATOM(tree))
	temp1 = tree;
    else {
	a = subst_if(new,test,M_CAR(tree),key);
	d = subst_if(new,test,M_CDR(tree),key);
	if (eql(a, M_CAR(tree)) && eql(d, M_CDR(tree)))
	    temp1 = tree;
	else
	    temp1 = cons(a,d);
    }
    RESTORE_STACK();
    return VALUES_1(temp1);
}
