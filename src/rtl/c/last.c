/*
 * last.c -  Chestnut Run-Time Library entry for function last
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "lists.h"

Object last (list, ln)
    Object list, ln;
{
    Declare_local_temp;
    Object lastcell;
    SI_Long n;

    if (UNSUPPLIED_P(ln))
	n = 1L;
    else
	n = IFIX(ln);
    
    lastcell = list;

    for(; n > 0; n--) {    /* n times */
	if (!CONSP(lastcell))
	    break;
	else
	    lastcell = M_CDR(lastcell);
    }

    if (n == 1)
	while(CONSP(lastcell)) {
	    list = lastcell;
	    lastcell = M_CDR(lastcell);
	}
    else {
	while(CONSP(lastcell)) {
	    list = M_CDR(list);
	    lastcell = M_CDR(lastcell);
	}
    }

    return VALUES_1(list);
}
