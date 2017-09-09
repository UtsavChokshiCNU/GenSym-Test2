/*
 * assocqul.c -  Chestnut Run-Time Library entry for function assoc_equal
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
	    
Object assoc_equal(key, alist)
    Object key, alist;
{
    Declare_local_temp;
    Object elem, elemkey;

    for ( ; CONSP(alist); alist = M_CDR(alist)) {
	elem = M_CAR(alist);
	if (!ENDP(elem)) {
	    elemkey = M_CAR(elem);
	    if (EQUAL(elemkey, key))
		return VALUES_1(elem);
	}
    }
    return VALUES_1(NIL);
}
