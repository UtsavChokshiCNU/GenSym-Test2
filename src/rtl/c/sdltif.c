/*
 * sdltif.c -  Chestnut Run-Time Library entry for function SI_delete_if
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern void SI_shorten_primitive_vector(Object pv, long len);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object funcall1(Object func, Object arg);
extern long ilength(Object sequence);
extern Object nreverse(Object);

#else

extern void SI_shorten_primitive_vector();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object funcall1();
extern long ilength();
extern Object nreverse();

#endif


#include "seqmodi.h"

with_shorten_vector() /* no semicolon */


Object SI_delete_if(pred, seq, from_end, lstart, lend, lcount, key, not_p)
    Object pred, seq, from_end, lstart, lend, lcount, key, not_p;
{
    Declare_local_temp;
    Object result = NIL, prev_cell = NIL;
    Object elem, rest, keyelem;
    long start, end, count, len, i, j, ndeleted = 0L;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_6(pred,seq,from_end,key,result,prev_cell);
    PROTECTI_3(elem,rest,keyelem);

    start = !UNSUPPLIED_P(lstart) ? IFIX(lstart) : 0L;
    len = ilength(seq);
    end = (SUPPLIEDP(lend) && TRUEP(lend)) ? IFIX(lend) : len;
    count = (SUPPLIEDP(lcount) && TRUEP(lcount)) ? IFIX(lcount) : (end-start);
    if (UNSUPPLIED_P(key)) key = NIL;

    if (SUPPLIEDP(from_end) && TRUEP(from_end) && lcount) {
	result = nreverse(SI_delete_if(pred, nreverse(seq), NIL,
			FIX(len-end), FIX(len-start),lcount, key, not_p));
    }
    else if (LISTP(seq)) {
	for (i = 0; (i < start) && TRUEP(seq); i++, seq = M_CDR(seq)) {
	    if (result == NIL)
		result = seq;
	    else
		RPLACD(prev_cell, seq);
	    prev_cell = seq;
	}
	for (i = start; (i < end) && TRUEP(seq) && (ndeleted < count);
	     i++, seq = M_CDR(seq)) {
	    elem = keyelem = M_CAR(seq);
	    if (TRUEP(key))
		keyelem = FUNCALL_1(key, elem);
	    if (TRUEP(not_p) ? TRUEP(FUNCALL_1(pred, keyelem))
		: !TRUEP(FUNCALL_1(pred, keyelem))) {
		/* Keep this item */
		if (result == NIL)
		    result = seq;
		else
		    RPLACD(prev_cell, seq);
		prev_cell = seq;
	    }
	    else {
		ndeleted++;
	    }
	}
	if (TRUEP(prev_cell))
	    RPLACD(prev_cell,seq);
	else
	    result = seq;
    }
    else {
	result = seq;
	for (i = start, j = start; i < end && ndeleted < count; i++) {
	    elem = do_aref_1(seq, i);
	    keyelem = TRUEP(key) ? FUNCALL_1(key,elem) : elem;
	    if (!TRUEP(not_p) ? TRUEP(FUNCALL_1(pred, keyelem))
		: !TRUEP(FUNCALL_1(pred, keyelem))) {
		ndeleted++;
	    }
	    else {
		if (ndeleted) {  /* only need to shift if one removed */
		    do_setf_aref(seq, j, elem);
		}
		j++;
	    }
	}
	if (ndeleted) {
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
