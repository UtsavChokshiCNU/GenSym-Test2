/*
 * count.c -  Chestnut Run-Time Library entry for function count
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
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);

#else

extern Object STATIC_FUNCTION1();
extern Object do_aref_1();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();

#endif


#include "lists.h"

Object count (item, seq, from_end, test, test_not, lstart, lend, key)
    Object item, seq, from_end, test, test_not, lstart, lend, key;
{
    Declare_local_temp;

    Object rest, elem;
    long n = 0L, i, start, end, len;
    Declare_stack_pointer;
    long testp = !UNSUPPLIED_P(test);

    SAVE_STACK();
    PROTECT_5(item,seq,test,test_not,key);
    PROTECTI_2(rest,elem);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }
    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    if (UNSUPPLIED_P(key)) key = NIL;
    if (UNSUPPLIED_P(from_end)) from_end = NIL;


    if (VECTORP(seq)) {
	while (start < end) {
	    elem = do_aref_1(seq,start);
	    if (TRUEP(key))
		elem = funcall1(key, elem);
	    if (SATISFIESP(testp, test, test_not, item,elem))
		n++;
	    start++;
	}	
    }
    else {
	for (i = 0L; TRUEP(seq) && (i < start); i++, seq = M_CDR(seq))
	    ;
	for (i = start; TRUEP(seq) && (i < end); i++, seq = M_CDR(seq)) {
	    elem = M_CAR(seq);
	    if (TRUEP(key))
	        elem = funcall1(key, elem);
	    if (SATISFIESP(testp, test, test_not, item,elem)) 
	        n++;
	}
    }
    RESTORE_STACK();
    return VALUES_1(FIX(n));
}
