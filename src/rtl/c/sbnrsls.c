/*
 * sbnrsls.c -  Chestnut Run-Time Library entry for function SI_obtain_rest_list
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




Object SI_obtain_rest_list (SI_rest_position, SI_arg_position, SI_nargs, SI_ap)
    long SI_rest_position, SI_arg_position, SI_nargs;
    va_list *SI_ap;
{
    Object result = NIL;
    long i;
    Stack_item *sp;

    while (SI_arg_position < SI_nargs) {

	STACK_PUSH(va_arg(*SI_ap, Object));
	++SI_arg_position;
    }
    sp = Stack;
    PROTECT_1(result);
    for (i = -1; SI_rest_position < SI_nargs; ++SI_rest_position, --i)
	result = cons(sp[i].object, result);
    Stack = sp + i;
    return result;
}
