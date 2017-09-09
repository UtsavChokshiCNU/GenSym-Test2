/*
 * nbutlast.c -  Chestnut Run-Time Library entry for function nbutlast
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern long ilength(Object sequence);
extern Object nthcdr(Object,Object);

#else

extern long ilength();
extern Object nthcdr();

#endif


#include "lists.h"

/* &optional 1 1 */
Object nbutlast (list, optn)
    Object list, optn;
{
    Declare_local_temp;
    long i, n, len = ilength(list);

    n = (UNSUPPLIED_P(optn)) ? 1L : IFIX(optn) ;
    if (n >= len)
	return VALUES_1(NIL);
    i = (len - n) - 1L;
    RPLACD(nthcdr(FIX(i), list), NIL);
    return VALUES_1(list);
}
