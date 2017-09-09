/*
 * makelist.c -  Chestnut Run-Time Library entry for function make_list
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);

#else

extern Object cons();

#endif


#include "lists.h"

Object make_list (lsize, initial_element)
    Object lsize, initial_element;
{
    Declare_local_temp;
    Object result = NIL;
    long size;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(initial_element,result);

    if (UNSUPPLIED_P(initial_element)) initial_element = NIL;
    size = IFIX(lsize);
    while (size--) {
	result = cons(initial_element, result);
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
