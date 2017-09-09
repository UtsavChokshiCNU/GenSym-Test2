/*
 * snsqncfn.c -  Chestnut Run-Time Library entry for function SI_init_sequence_fn
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern long ilength(Object sequence);

#else

extern long ilength();

#endif




Object SI_init_sequence_fn (seq, lstart, lend, pstart, pend)
    Object seq, lstart, lend;
    long *pstart, *pend;
{
    Declare_local_temp;
    long i;

    *pstart = SUPPLIEDP(lstart) ? IFIX(lstart) : 0L;
    *pend = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : ilength(seq);

    if (LISTP(seq)) {
	for (i = 0; TRUEP(seq) && (i < *pstart); i++) {
	    seq = M_CDR(seq);
	}
    }
    return(seq);
}
