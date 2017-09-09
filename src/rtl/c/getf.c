/*
 * getf.c -  Chestnut Run-Time Library entry for function getf
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/* &optional 2 1  */
Object getf (list, indicator, ldefault)
    Object list, indicator, ldefault;
{
    Declare_local_temp;
    Object next_cdr;

    while(TRUEP(list)) {
	next_cdr = M_CDR(list);
	if (indicator == M_CAR(list)) {
	    return VALUES_1(M_CAR(next_cdr));
	}
	list = M_CDR(next_cdr);
    }
    return VALUES_1(SUPPLIED_P(ldefault) ? ldefault : NIL);
}
