/*
 * ldelete.c -  Chestnut Run-Time Library entry for function ldelete
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object SI_fp_eql_1;

#if SI_USE_PROTOTYPES

extern void SI_shorten_primitive_vector(Object pv, long len);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern void SI_shorten_primitive_vector();
extern Object STATIC_FUNCTION1();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();
extern Object nreverse();

#endif


#include "seqmodi.h"

with_shorten_vector() /* no semicolon */


Object ldelete (item, seq, from_end, test, test_not, lstart, lend, lcount, key)
    Object item, seq, from_end, test, test_not, lstart, lend, lcount, key;
{
    Declare_local_temp;
    Object result = NIL, prev_cell = NIL;
    Object elem, keyelem, delete_p, rest;
    long start, end, count, len, i, j, nremoved = 0L;
    Declare_stack_pointer;
    long testp = !UNSUPPLIED_P(test);

    SAVE_STACK();
    PROTECT_8(item,seq,from_end,test,test_not,key,result,prev_cell);
    PROTECTI_4(elem,keyelem,delete_p,rest);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    count = (SUPPLIEDP(lcount) && TRUEP(lcount)) ? IFIX(lcount) : (end-start);
    if (UNSUPPLIED_P(key)) key = NIL;

    if (SUPPLIEDP(from_end) && TRUEP(from_end) && lcount) {
	result = nreverse(ldelete(item, nreverse(seq), NIL, test, test_not,
			FIX(len-end), FIX(len-start), lcount, key));
    }
    else if (LISTP(seq)) {
	for (i = 0; (i < start) && TRUEP(seq); i++, seq = M_CDR(seq)) {
	    if (result == NIL)
		result = seq;
	    else
		RPLACD(prev_cell, seq);
	    prev_cell = seq;
	}
	for (i = start; (i < end) && TRUEP(seq) && (nremoved < count);
	     i++, seq = M_CDR(seq)) {
	    elem = M_CAR(seq);
	    keyelem = TRUEP(key) ? FUNCALL_1(key,elem) : elem;
	    if (SATISFIESP(testp, test, test_not, item, keyelem))
		delete_p = T;
	    else
		delete_p = NIL;
	    if (!TRUEP(delete_p)) {
		if (result == NIL)
		    result = seq;
		else
		    RPLACD(prev_cell, seq);
		prev_cell = seq;
	    }
	    else {
		nremoved++;
	    }
	}
	if (TRUEP(prev_cell))
	    RPLACD(prev_cell, seq);
	else
	    result = seq;
    }
    else {
	result = seq;
	for (i = start, j = start; i < end && nremoved < count; i++) {
	    elem = do_aref_1(seq, i);
	    keyelem = TRUEP(key) ? FUNCALL_1(key,elem) : elem;
	    if (SATISFIESP(testp,test,test_not, item, keyelem)) {
		nremoved++;
	    }
	    else {
		if (nremoved) {  /* only need to shift if one removed */
		    do_setf_aref(seq, j, elem);
		}
		j++;
	    }
	}
	if (nremoved) {
	    while (i < len) {
		do_setf_aref(seq, j, do_aref_1(seq, i));
		i++;
		j++;
	    }
	    shorten_vector(seq, j);
	}
    }

    RESTORE_STACK();
    return VALUES_1(result);
}
