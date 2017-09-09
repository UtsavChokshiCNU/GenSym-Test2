/*
 * position.c -  Chestnut Run-Time Library entry for function position
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
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern Object STATIC_FUNCTION1();
extern Object copy_seq();
extern Object do_aref_1();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();
extern Object nreverse();

#endif


#include "lists.h"

Object position (item, seq, from_end, test, test_not, lstart, lend, key)
    Object item, seq, from_end, test, test_not, lstart, lend, key;
{
    Declare_local_temp;
    long i, start, end, len;
    Object rest, elem, result;
    Declare_stack_pointer;
    long negatep = FALSE, keyp;

    SAVE_STACK();
    PROTECT_5(item,seq,test,test_not,key);
    PROTECTI_3(rest,elem,result);

    keyp = !UNSUPPLIED_P(key);
    if (UNSUPPLIED_P(from_end)) from_end = NIL;
    if (UNSUPPLIED_P(test)) {
	if (UNSUPPLIED_P(test_not))
	    test = FP_EQL;
	else
	    negatep = TRUE;
    }
    start = UNSUPPLIED_P(lstart) ? 0L : IFIX(lstart);
    end = UNSUPPLIED_P(lend) ? (len = ilength(seq)) : IFIX(lend);
    result = NIL;

    if (VECTORP(seq)) {
	if (TRUEP(from_end)) {
	    end--;
	    while (end >= start) {
		elem = do_aref_1(seq, end);
		if (keyp)
		    elem = FUNCALL_1(key,elem);
		if (negatep ? !TRUEP(FUNCALL_2(test_not,item,elem))
			    : TRUEP(FUNCALL_2(test,item,elem))) {
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
	        if (keyp)
		    elem = FUNCALL_1(key, elem);
		if (negatep ? !TRUEP(FUNCALL_2(test_not,item,elem))
			    : TRUEP(FUNCALL_2(test,item,elem))) {
		    result = FIX(start);
		    break;
		}
		start++;
	    }
	    if (end == start) result = NIL;
	}	
    }
    else if (TRUEP(from_end)) {
	result = position(item, nreverse(copy_seq(seq)), NIL, test,test_not,
			  FIX(len-end), FIX(len-start), key);
	if (TRUEP(result)) result = FIX(len - 1 - IFIX(result));
    }
    else {
	for (rest = seq, i = 0L; TRUEP(rest); rest = M_CDR(rest),
	     ++i) {
	    if (i >= end)
		break;
	    if (i >= start) {
		elem = M_CAR(rest);
		if (keyp)
		    elem = FUNCALL_1(key, elem);
		if (negatep ? !TRUEP(FUNCALL_2(test_not,item,elem))
			    : TRUEP(FUNCALL_2(test,item,elem))) {
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
