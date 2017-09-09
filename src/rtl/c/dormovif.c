/*
 * dormovif.c -  Chestnut Run-Time Library entry for function do_remove_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_delete_if(Object pred, Object seq, Object from_end, Object lstart, Object lend, Object lcount, Object key, Object not_p);
extern Object cons(Object,Object);
extern Object copy_seq(Object);
extern Object funcall1(Object func, Object arg);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern Object SI_delete_if();
extern Object cons();
extern Object copy_seq();
extern Object funcall1();
extern long ilength();
extern Object nreverse();

#endif


#include "seqmodi.h"

static Object do_remove_if(pred,seq,from_end,lstart,lend,lcount,key, not_p)
    Object pred,seq,from_end,lstart,lend,lcount,key, not_p;
{
    Declare_local_temp;
    Object result = NIL, elem, keyelem;
    long start, end, count, len, i, nremoved = 0L;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(pred,seq,from_end,key,result);
    PROTECTI_2(elem,keyelem);

    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    count = (SUPPLIEDP(lcount) && TRUEP(lcount)) ? IFIX(lcount) : (end-start);
    if (UNSUPPLIED_P(key)) key = NIL;

    if (SUPPLIEDP(from_end) && TRUEP(from_end) && lcount) {
	result = nreverse(SI_delete_if(pred, nreverse(copy_seq(seq)), NIL,
			FIX(len-end), FIX(len-start), lcount, key, not_p));
    }
    else if (LISTP(seq)) {
	for (i = 0; (i < start) && TRUEP(seq); i++, seq = M_CDR(seq))
	    result = cons(M_CAR(seq), result);
	for (i = start; (i < end) && (nremoved < count) && TRUEP(seq);
	     i++, seq = M_CDR(seq)) {
	    elem = keyelem = M_CAR(seq);
	    if (TRUEP(key))
		keyelem = FUNCALL_1(key, elem);
	    if (TRUEP(not_p) ? TRUEP(FUNCALL_1(pred, keyelem))
		: !TRUEP(FUNCALL_1(pred, keyelem))) {
		result = cons(elem, result);
	    }
	    else
		nremoved++;
	}
	for (i = start; (i < len) && TRUEP(seq); i++, seq = M_CDR(seq))
	    result = cons(M_CAR(seq), result);
	result = nreverse(result);
    }
    else {
	result = SI_delete_if(pred, copy_seq(seq), from_end,
			lstart, lend, lcount, key, not_p);
    }

    RESTORE_STACK();
    return VALUES_1(result);
}

Object remove_if (test, sequence, from_end, start, end, count, key)
    Object test, sequence, from_end, key;
    Object start, end, count;
{
    return do_remove_if(test, sequence,from_end,start,end,count,key, NIL);
}

Object remove_if_not (test, sequence, from_end, start, end, count, key)
    Object test, sequence, from_end, key;
    Object start, end, count;
{
    return do_remove_if(test, sequence,from_end,start,end,count,key, T);
}

