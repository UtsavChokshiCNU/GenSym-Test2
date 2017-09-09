/*
 * lremove.c -  Chestnut Run-Time Library entry for function lremove
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
extern Object cons(Object,Object);
extern Object copy_seq(Object);
extern Object eql(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);
extern Object ldelete(Object item, Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object lcount, Object key);
extern Object nreverse(Object);

#else

extern Object STATIC_FUNCTION1();
extern Object cons();
extern Object copy_seq();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();
extern Object ldelete();
extern Object nreverse();

#endif


#include "seqmodi.h"

Object lremove (item, seq, from_end, test, test_not, lstart, lend, lcount, key)
    Object item, seq, from_end, test, test_not;
    Object lstart, lend, lcount, key;
{
    Declare_local_temp;
    long i, start, end, count, nremoved = 0, len;
    Object result = NIL, prev_cell = NIL, new_cell;
    Object elem, keyelem;
    Declare_stack_pointer;
    long testp = !UNSUPPLIED_P(test);

    SAVE_STACK();
    PROTECT_7(item,seq,test,test_not,key,result,prev_cell);
    PROTECTI_3(new_cell,elem,keyelem);

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
	result = nreverse(ldelete(item, nreverse(copy_seq(seq)), NIL,
			test, test_not, FIX(len-end), FIX(len-start),
			lcount, key));
    }
    else if (LISTP(seq)) {
	    for (i = 0; (i < start) && TRUEP(seq); seq = M_CDR(seq), i++) {
	        result = cons(M_CAR(seq), result);
	    }
	    while(seq && (start < end) && (nremoved < count)) {
	        elem = keyelem = M_CAR(seq);
	        if (TRUEP(key))
		    keyelem = FUNCALL_1(key, elem);
		if (SATISFIESP(testp, test, test_not, item, keyelem)) {
		    nremoved++;
	        }
		else {
		    result = cons(elem, result);
		}
		seq = M_CDR(seq);
		start++;
	    }
	    for (i = start; TRUEP(seq) && (i < len); i++, seq = M_CDR(seq)) {
	        result = cons(M_CAR(seq), result);
	    }
	    result = nreverse(result);
    }
    else {
	result = ldelete(item, copy_seq(seq), from_end,
			test, test_not, lstart, lend, lcount, key);
    }

    RESTORE_STACK();
    return VALUES_1(result);
}
