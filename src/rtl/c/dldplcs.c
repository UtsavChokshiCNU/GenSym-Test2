/*
 * dldplcs.c -  Chestnut Run-Time Library entry for function delete_duplicates
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
extern Object member_se(Object item, Object list, Object test, Object test_not, Object key, Object start, Object end);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);
extern Object nreverse(Object);
extern Object nthcdr(Object,Object);

#else

extern void SI_shorten_primitive_vector();
extern Object STATIC_FUNCTION1();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object eql();
extern Object funcall1();
extern Object funcall2();
extern long ilength();
extern Object member_se();
extern Object member();
extern Object nreverse();
extern Object nthcdr();

#endif


#include "seqmodi.h"

FORWARD_STATIC Object vector_member();

with_shorten_vector() /* no semicolon */

Object delete_duplicates (seq, from_end, test, test_not, lstart, lend, key)
    Object seq, from_end, test, test_not, lstart, lend, key;
{
    Declare_local_temp;
    Object item, temp, prev = NIL, result = NIL, saveend, found_p;
    Object elem, keyelem;
    long i, j, len, start, end, nremoved;
    Declare_stack_pointer;
    long testp = !UNSUPPLIED_P(test);

    SAVE_STACK();
    PROTECT_7(seq,from_end,test,test_not,key,result,prev);
    PROTECTI_6(item,elem,keyelem,temp,saveend,found_p);
 
    if (!testp && UNSUPPLIED_P(test_not)) {
	test = FP_EQL;
	testp = TRUE;
    }

    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    if (UNSUPPLIED_P(key)) key = NIL;

    if (SUPPLIEDP(from_end) && TRUEP(from_end)) {
	result = nreverse(delete_duplicates(nreverse(seq),NIL,test,test_not,
					    FIX(len-end),FIX(len-start),key));
    }
    else if (VECTORP(seq)) {
	result = seq;
	nremoved = 0;
	for (i = start, j = start; i < end; i++) {
	    elem = do_aref_1(seq, i);
	    keyelem = (TRUEP(key)) ? FUNCALL_1(key,elem) : elem;
	    if (TRUEP(vector_member(keyelem, seq, i+1, end,
				    test, test_not, key))) {
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
    else {
	saveend = (SUPPLIEDP(lend) && TRUEP(lend)) 
	    ? nthcdr(FIX(end), seq) : NIL;
	result = seq;
	for (i = 0; TRUEP(seq) && (i < start); i++)
	    prev = seq = M_CDR(seq);
	for (i = start; TRUEP(seq) && (i < end); i++) {
	    item = M_CAR(seq);
	    if (TRUEP(key))
		item = FUNCALL_1(key, item);
	    if (SUPPLIEDP(lend) && TRUEP(lend)) 
		found_p = member_se(item, M_CDR(seq),test,test_not,key,
				    _,saveend);
	    else
		found_p = member(item,M_CDR(seq),test,test_not,key);
	    if (TRUEP(found_p)) {
		if (TRUEP(prev)) {
		    RPLACD(prev,M_CDR(seq));
		}
		else {
		    result = M_CDR(seq);
		    prev = NIL;
		}
	    }
	    else {
		prev = seq;
	    }
	    seq = M_CDR(seq);
	}
    }
    RESTORE_STACK();
    return VALUES_1(result);
}

/* One of test or test_not *must* be supplied. */
static Object vector_member (item, seq, start, end, test, test_not, key)
    Object item, seq, test, test_not, key;
    long start, end;
{
    Declare_local_temp;
    long i;
    Object result, elem;
    Declare_stack_pointer;

    /* may be able to remove GC stuff if guarantee no consing by key or test */
    SAVE_STACK();
    PROTECT_5(item,seq,test,test_not,key);
    PROTECTI_2(result,elem);

    result = NIL;
    for (i = start; i < end; i++) {
	elem = do_aref_1(seq, i);
	if (SUPPLIEDP(key) && TRUEP(key)) /* default = NIL */
	    elem = FUNCALL_1(key, elem);
	if (SUPPLIEDP(test) ? TRUEP(FUNCALL_2(test, item, elem))
			    : !TRUEP(FUNCALL_2(test_not, item, elem))) {
	    result = T;
	    break;
	}
    }

    RESTORE_STACK();
    return VALUES_1(result);
}


