/*
 * nconc2.c -  Chestnut Run-Time Library entry for function nconc2
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object nconc2 (list1, list2)
    Object list1, list2;
{
    Declare_local_temp;
    Object result, lastcell;

    if (ENDP(list1)) {
	result = list2;
    }
    else if (ENDP(list2)) {
	result = list1;
    }
    else {
	result = lastcell = list1;
	while(!ENDP(lastcell)) {
	    list1 = lastcell;
	    lastcell = M_CDR(lastcell);
	}

        RPLACD(list1, list2);
    }
    return VALUES_1(result);
}
