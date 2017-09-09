/*
 * set_getf.c -  Chestnut Run-Time Library entry for function set_getf
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




Object set_getf (list, indicator, value)
    Object list, indicator, value;
{
    Declare_local_temp;
    Object next_cdr;
    Object tail = list;
    Object temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_4(list,indicator,value,tail);
    PROTECTI_2(next_cdr,temp);
    while(TRUEP(tail)) {
	next_cdr = M_CDR(tail);
	if (indicator == M_CAR(tail)) {
	    RPLACA(next_cdr, value);
	    RESTORE_STACK();
	    return VALUES_1(list);
	}
	tail = M_CDR(next_cdr);
    }
    temp = cons(value,list);
    RESTORE_STACK();
    return cons(indicator, temp);
}
