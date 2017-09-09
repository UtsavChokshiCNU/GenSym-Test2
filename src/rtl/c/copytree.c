/*
 * copytree.c -  Chestnut Run-Time Library entry for function copy_tree
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object ncons1(Object a);

#else

extern Object ncons1();

#endif


#include "lists.h"

Object copy_tree (tree)
    Object tree;
{
    Declare_local_temp;
    Object result, new_cell, last_cell;
    Declare_stack_pointer;

    if (ATOM(tree))
	return VALUES_1(tree);
    SAVE_STACK();
    PROTECT_1(tree);
    PROTECTI_3(result,new_cell,last_cell);
    result = last_cell = ncons1(copy_tree(M_CAR(tree)));
    tree = M_CDR(tree);
    while(CONSP(tree)) {
	new_cell = ncons1(copy_tree(M_CAR(tree)));
	RPLACD(last_cell, new_cell);
	last_cell = new_cell;
	tree = M_CDR(tree);
    }
    /* end with NIL or dotted atom */
    RPLACD(last_cell, tree);
    RESTORE_STACK();
    return VALUES_1(result);
}
