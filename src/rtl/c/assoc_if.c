/*
 * assoc_if.c -  Chestnut Run-Time Library entry for function assoc_if
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
	    
Object assoc_if (pred, a_list, key)
        Object pred, a_list, key;
{
    Declare_local_temp;
    Object pair, elemkey;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(pred, a_list, key);

    if (!SUPPLIEDP(key))
	key = NIL;

    PROTECTI_2(pair, elemkey);

    for (;CONSP(a_list); a_list = M_CDR(a_list)) {
	pair = M_CAR(a_list);
	if (CONSP(pair)) {
	    elemkey = M_CAR(pair);
	    if TRUEP(key)
		elemkey = funcall1(key, elemkey);
	    if (TRUEP(funcall1(pred, elemkey))) {
		RESTORE_STACK();
		return VALUES_1(pair);
	    }
	}
    }

    RESTORE_STACK();
    return VALUES_1(NIL);
}
