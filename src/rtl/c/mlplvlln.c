/*
 * mlplvlln.c -  Chestnut Run-Time Library entry for function multiple_value_list_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);

#else

extern Object cons();

#endif





Object multiple_value_list_n (n, value1)
    Object n;
    Object value1;
{
    Object result = NIL;
    Declare_stack_pointer;
    long i;

    SAVE_STACK();
    PROTECT_2(value1,result);

    i = IFIX(n);
    if (!i)
	return(VALUES_0());
    i--;
    while(i) {
	i--;
	result = cons(Values[i], result);  
    }
    RESTORE_STACK();
    return(cons(value1, result));
}
