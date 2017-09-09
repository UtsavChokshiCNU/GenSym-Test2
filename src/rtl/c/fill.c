/*
 * fill.c -  Chestnut Run-Time Library entry for function fill
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object do_setf_aref();

#endif


#include "seqmodi.h"

extern Object SI_init_sequence_fn();

Object fill (seq, item, lstart, lend)
    Object seq, item, lstart, lend;
{
    Declare_local_temp;
    long start, end;
    Object result = seq;

    seq = SI_init_sequence_fn(seq, lstart, lend, &start, &end);
    if (VECTORP(seq)) {
	while (start < end) {
	    do_setf_aref(seq, start, item);
	    start++;
	}
    }
    else {
	while (TRUEP(seq) && (start < end)) {
	    M_CAR(seq) = item;
	    seq = M_CDR(seq);
	    start++;
	}
    }

    return VALUES_1(result);
}
