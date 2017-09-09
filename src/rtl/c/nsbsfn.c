/*
 * nsbsfn.c -  Chestnut Run-Time Library entry for function nsubstitute_if_not
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_fp_eql_1;

#if SI_USE_PROTOTYPES

extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern Object STATIC_FUNCTION1();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object eql();
extern Object funcall1();
extern long ilength();
extern Object nreverse();

#endif


#include "seqmodi.h"

Object nsubstitute_if_not (newitem, test, seq, from_end, lstart, lend,
			  lcount, key)
    Object newitem, test, seq, from_end, lstart, lend, lcount, key;
{
    Declare_local_temp;
    Object elem, result = NIL;
    long i, len, start, end, count, nsubs = 0;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(newitem,test,seq,key,result);
    PROTECTI_1(elem);

    if (UNSUPPLIED_P(test)) test = FP_EQL;
    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    count = (SUPPLIEDP(lcount) && TRUEP(lcount)) ? IFIX(lcount) : (end-start);
    if (UNSUPPLIED_P(key)) key = NIL;

    if (SUPPLIEDP(from_end) && TRUEP(from_end) && lcount) {
	result = nreverse(nsubstitute_if_not(newitem, test, nreverse(seq), NIL,
			FIX(len-end),FIX(len-start),lcount,key));
    }
    if (VECTORP(seq)) {
	result = seq;
	for (i = start; (nsubs < count) && (i < end); i++) {
	    elem = do_aref_1(seq, i);
	    if (TRUEP(key))
		elem = FUNCALL_1(key,elem);
	    if (!TRUEP(FUNCALL_1(test, elem))) {
		do_setf_aref(seq, i, newitem);
		nsubs++;
	    }
	}
    }
    else {
	result = seq;
	for (i = 0; TRUEP(seq) && (i < start); i++, seq = M_CDR(seq))
	    ;
	for (i = start; TRUEP(seq) && (i < end) && (nsubs < count);
	     i++, seq = M_CDR(seq)) {
	    elem = M_CAR(seq);
	    if (TRUEP(key))
		elem = FUNCALL_1(key, elem);
	    if (!TRUEP(FUNCALL_1(test,elem))) {
		RPLACA(seq, newitem);
		nsubs++;
	    }
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
