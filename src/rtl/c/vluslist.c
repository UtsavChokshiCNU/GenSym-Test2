/*
 * vluslist.c -  Chestnut Run-Time Library entry for function values_list
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];



Object values_list (args)
    Object args;
{
    register long i;
    Object arg1;

    Values_count = 0;
    if (args) {
	Values_count++;
	arg1 = M_CAR(args);
	args = M_CDR(args);
	for (i = 0; args; i++) {
	    Values_count++;
	    Values[i] = M_CAR(args);
	    args = M_CDR(args);
	}
	return(arg1);
    }
    return VALUES_0();
}
