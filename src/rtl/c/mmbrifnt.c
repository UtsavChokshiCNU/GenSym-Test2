/*
 * mmbrifnt.c -  Chestnut Run-Time Library entry for function member_if_not
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

Object member_if_not (pred, list, key)
    Object pred, list, key;
{
    Declare_local_temp;
    Object elemkey;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(pred,list,key);
    PROTECTI_1(elemkey);

    if (UNSUPPLIED_P(key)) key = NIL;
    while (!ENDP(list)) {
	elemkey = M_CAR(list);
	if (TRUEP(key))
	    elemkey = funcall1(key, elemkey);
	if (!TRUEP(funcall1(pred, elemkey))) {
	    RESTORE_STACK();
	    return VALUES_1(list);
	}
	list = M_CDR(list);
    }
    RESTORE_STACK();
    return VALUES_1(NIL);
}
