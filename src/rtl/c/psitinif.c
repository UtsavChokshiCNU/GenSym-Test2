/*
 * psitinif.c -  Chestnut Run-Time Library entry for function position_if
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
extern Object copy_seq(Object);
extern Object do_aref_1(Object arr, long i);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern Object STATIC_FUNCTION1();
extern Object copy_seq();
extern Object do_aref_1();
extern Object eql();
extern Object funcall1();
extern long ilength();
extern Object nreverse();

#endif


#include "lists.h"

Object position_if (test, seq, from_end, lstart, lend, key)
    Object test, seq, from_end, lstart, lend, key;
{
    Declare_local_temp;
    Object rest, elem, result;
    long i, start, end, len;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(test,seq,key);
    PROTECTI_3(rest,elem,result);

    if (UNSUPPLIED_P(test)) test = FP_EQL; 
    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;

    if (UNSUPPLIED_P(key)) key = NIL;
    if (UNSUPPLIED_P(from_end)) from_end = NIL;

    result = NIL;

    if (VECTORP(seq)) {
	if (TRUEP(from_end)) {
	    end--;
	    while (end >= start) {
		elem = do_aref_1(seq,end);
		if (TRUEP(key))
		    elem = funcall1(key, elem);
		if (funcall1(test, elem)) {
		    result = FIX(end);
		    break;
		}
		end--;
	    }
	    if (end == start) result = NIL;
	}
	else {
	    while (start < end) {
		elem = do_aref_1(seq,start);
		if (TRUEP(key))
		    elem = funcall1(key, elem);
		if (funcall1(test, elem)) {
		    result = FIX(start);
		    break;
		}
		start++;
	    }
	    if (end == start) result = NIL;
	}	
    }
    else if (TRUEP(from_end)) {
	result = position_if(test, nreverse(copy_seq(seq)), NIL,
			     FIX(len-end), FIX(len-start), key);
	if (TRUEP(result)) result = FIX(len - 1 - IFIX(result));

    }
    else {
	for (rest = seq, i = 0L; TRUEP(rest); rest = CDR(rest),
	     ++i) {
	    if (i >= end)
		break;
	    if (i >= start) {
		elem = M_CAR(rest);
		if (TRUEP(key))
		    elem = funcall1(key, elem);
		if (funcall1(test, elem)) {
		    result = FIX(i);
		    break;
		}
	    }
	}
	if (ENDP(rest) || i == end) result = NIL;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
