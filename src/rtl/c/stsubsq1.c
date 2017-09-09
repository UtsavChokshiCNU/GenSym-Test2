/*
 * stsubsq1.c -  Chestnut Run-Time Library entry for function set_subseq1
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object elt(Object,Object);
extern long ilength(Object sequence);

#else

extern Object do_setf_aref();
extern Object elt();
extern long ilength();

#endif




Object set_subseq1 (seq,lstart,new_seq)
    Object seq, lstart, new_seq;
{
    Declare_local_temp;
    long i, start, end, len;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(seq, new_seq);

    start = TRUEP(lstart) ? IFIX(lstart) : 0L;
    len = ilength(new_seq);
    end = ilength(seq);

    if (LISTP(seq)) {
	for (i = 0; seq && (i < start); i++)
	    seq = M_CDR(seq);
	for (i = 0; (i < len) && (start < end) && TRUEP(seq); i++, start++) {
	    M_CAR(seq) = elt(new_seq, FIX(i));
	    seq = M_CDR(seq);
	}
    }
    else {
	for (i = 0; (start < end) && (i < len); i++, start++) {
	    do_setf_aref(seq, start, elt(new_seq, FIX(i)));
	}
    }
    RESTORE_STACK();
    return(new_seq);
}
