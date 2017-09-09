/*
 * search.c -  Chestnut Run-Time Library entry for function search
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
extern Object elt(Object,Object);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);

#else

extern Object STATIC_FUNCTION1();
extern Object elt();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();

#endif


#include "lists.h"

Object search (seq1, seq2, from_end, test, test_not, key,
	      lstart1, lstart2, lend1, lend2)
    Object seq1, seq2, from_end, test, test_not, key;
    Object lstart1, lstart2, lend1, lend2;
{
    Declare_local_temp;
    long start1, start2, end1, end2, s1, s2, len;
    Object e1, e2, result;
    Declare_stack_pointer;
    long testp = !UNSUPPLIED_P(test);

    SAVE_STACK();
    PROTECT_5(seq1,seq1,test,test_not,key);
    PROTECTI_3(e1,e2,result);

    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    start1 = !UNSUPPLIED_P(lstart1) ? IFIX(lstart1) : 0L;
    start2 = !UNSUPPLIED_P(lstart2) ? IFIX(lstart2) : 0L;
    len = ilength(seq1);
    end1 = (SUPPLIEDP(lend1) && TRUEP(lend1)) ? IFIX(lend1) : len;
    len = ilength(seq2);
    end2 = (SUPPLIEDP(lend2) && TRUEP(lend2)) ? IFIX(lend2) : len;
    if (UNSUPPLIED_P(key)) key = NIL;
    if (UNSUPPLIED_P(from_end)) from_end = NIL;

    /* future: optimized this to handle different type of sequences separately
     * e.g. 2 strings:  strstr(ISTRING(seq2),ISTRING(seq1))
     */
    result = NIL;
    while (start2 < end2) {
	for (s1 = start1, s2 = start2; (s1 < end1) && (s2 < end2); s1++,s2++) {
	    e1 = elt(seq1,FIX(s1));
	    if (TRUEP(key))
	        e1 = funcall1(key,e1);
	    e2 = elt(seq2, FIX(s2));
	    if (TRUEP(key))
	        e2 = funcall1(key,e2);
	    if (!SATISFIESP(testp, test, test_not, e1,e2))
		break;
	}
	if (s1 == end1) {
	    result = FIX(start2);
	    if (!TRUEP(from_end))
		break;
	}
	start2++;
    }
    RESTORE_STACK();
    return VALUES_1(result);
}
