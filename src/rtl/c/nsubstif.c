/*
 * nsubstif.c -  Chestnut Run-Time Library entry for function nsubst_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object funcall1(Object func, Object arg);

#else

extern Object funcall1();

#endif


#include "lists.h"

Object nsubst_if (new, test, tree, key)
    Object new, test, tree, key;
{
    Declare_local_temp;
    Object treeitem;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(new,test,tree,key);
    PROTECTI_1(treeitem);
    if (UNSUPPLIED_P(key)) key = NIL;
    treeitem = (TRUEP(key)) ? funcall1(key, tree) : tree;
    if (TRUEP(funcall1(test, treeitem))) {
	RESTORE_STACK();
	return VALUES_1(new);
    }
    if (CONSP(tree)) {
	/* replacX should not evaluate consing 2-nd argument */
	treeitem = nsubst_if(new, test, M_CAR(tree), key);
	RPLACA(tree, treeitem);
	treeitem = nsubst_if(new, test, M_CDR(tree), key);
	RPLACD(tree, treeitem);
    }
    RESTORE_STACK();
    return VALUES_1(tree);
}
