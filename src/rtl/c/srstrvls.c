/*
 * srstrvls.c -  Chestnut Run-Time Library entry for function SI_restore_values
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_warn_fptr) ();

#endif



Object SI_restore_values ()
{
    long i, j;
    Object result = NIL;
    Object count = STACK_REF(-1L);

    if (!FIXNUMP(count))
	warn(1, "RESTORE_VALUES: stack seems to be corrupt");
    Values_count = IFIX(count);

    if (Values_count > 0) {
	j = -1L - Values_count;
	result = STACK_REF(j++);
	for (i = 0; j < -1L;)
	    Values[i++] = STACK_REF(j++);
    }
    Stack -= Values_count + 1L;
    return result;
}
