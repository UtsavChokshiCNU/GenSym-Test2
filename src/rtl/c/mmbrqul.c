/*
 * mmbrqul.c -  Chestnut Run-Time Library entry for function member_equal
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object equal(Object,Object);

#else

extern Object equal();

#endif


#include "lists.h"

Object member_equal (item, list)
    Object item, list;
{
    Declare_local_temp;
    Object entry;
    
    while (!ENDP(list)) {
	entry = M_CAR(list);
	if (EQUAL(item, entry))
	    return VALUES_1(list);
	else
	    list = M_CDR(list);
    }
    return VALUES_1(NIL);
}
