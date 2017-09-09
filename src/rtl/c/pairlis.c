/*
 * pairlis.c -  Chestnut Run-Time Library entry for function pairlis
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object nconc2(Object list1, Object list2);
extern Object nreverse(Object);

#else

extern Object cons();
extern Object nconc2();
extern Object nreverse();

#endif


#include "lists.h"

Object pairlis (keys,data,a_list)
    Object keys;
    Object data;
    Object a_list;
{
    Declare_local_temp;
    Object key, temp1, temp2, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(keys,data,a_list);
    PROTECTI_4(key,temp1,temp2,result);
    result = NIL;;
    for (temp1 = keys; TRUEP(temp1); temp1 = M_CDR(temp1)) {
	key = M_CAR(temp1);
	temp2 = CAR(data);
	data = CDR(data);
	result = cons(cons(key,temp2),result);
    }
    if (UNSUPPLIED_P(a_list)) a_list = NIL;
    result = nconc2(nreverse(result),a_list);
    RESTORE_STACK();
    return VALUES_1(result);
}
