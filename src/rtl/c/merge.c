/*
 * merge.c -  Chestnut Run-Time Library entry for function merge
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qsimple_vector;

#if SI_USE_PROTOTYPES

extern Object cons(Object,Object);
extern Object elt(Object,Object);
extern Object funcall1(Object func, Object arg);
extern Object funcall2(Object func, Object arg1, Object arg2);
extern long ilength(Object sequence);
extern Object list_length(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_sequence(Object type, Object lsize, Object initial_element);
extern Object set_elt(Object,Object,Object);

#else

extern Object cons();
extern Object elt();
extern Object funcall1();
extern Object funcall2();
extern long ilength();
extern Object list_length();
extern Object make_array();
extern Object make_sequence();
extern Object set_elt();

#endif



FORWARD_STATIC Object merge_list();
FORWARD_STATIC Object merge_elt();

Object merge (result_type, seq1, seq2, pred, key)
    Object result_type, seq1, seq2, pred, key;
{
    Declare_local_temp;
    Object result;

    if (VECTORP(seq1) || VECTORP(seq2))
	result = merge_elt(result_type, seq1, seq2, pred, key);
    else
	result = merge_list(result_type, seq1, seq2, pred, key);
    return VALUES_1(result);
}

static Object merge_list (result_type, seq1, seq2, pred, key)
    Object result_type, seq1, seq2, pred, key;
{
    Declare_local_temp;
    Object lst1_h, ptr, temp1, temp2, e1, e2;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(result_type,seq1,seq2,pred,key);
    PROTECTI_6(lst1_h,ptr,temp1,temp2,e1,e2);
    if (UNSUPPLIED_P(key)) key = NIL;

    for ((lst1_h = cons(NIL,seq1)), (ptr = lst1_h); CONSP(seq2);
		ptr = CDR(ptr)) {
	if (!TRUEP(CDR(ptr))) {
	    RPLACD(ptr,seq2);
	    temp1 = CDR(lst1_h);
	    goto LABEL1;
	}
	e1 = TRUEP(key) ? funcall1(key,CAR(seq2)) : CAR(seq2);
	e2 = TRUEP(key) ? funcall1(key,CADR(ptr)) : CADR(ptr);
	if (TRUEP(funcall2(pred,e1,e2))) {
	    /* splice old cons at head of seq2 into new sequence */
	    temp2 = seq2;
	    seq2 = CDR(seq2);
	    RPLACD(temp2, M_CDR(ptr));
	    RPLACD(ptr, temp2);
	}
    }
    temp1 = CDR(lst1_h);
    LABEL1: 
    RESTORE_STACK();
    /* if result_type is simple-vector,
       make array with initial content temp1 */
    if (EQ(result_type, Qsimple_vector))
        temp1 = make_array(list_length(temp1), _, _, temp1, _, _, _, _);
    return VALUES_1(temp1);
}

static Object merge_elt (result_type, seq1, seq2, pred, key)
    Object result_type, seq1, seq2, pred, key;
{
    Declare_local_temp;
    long len1, len2, new_len, i, i1, i2;
    Object new_seq, e1, e2, x1, x2;

    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_5(result_type,seq1,seq2,pred,key);
    PROTECTI_5(new_seq, e1, e2, x1, x2);

    len1 = ilength(seq1);
    len2 = ilength(seq2);
    if (UNSUPPLIED_P(key)) key = NIL;
    new_len = len1+len2;
    new_seq = make_sequence(result_type, FIX(new_len), NIL);
    for (i = 0, i1 = 0, i2 = 0; (i1 < len1) && (i2 < len2); i++) {
	x1 = elt(seq1, FIX(i1));
	e1 = TRUEP(key) ? funcall1(key, x1) : x1;
	x2 = elt(seq2, FIX(i2));
	e2 = TRUEP(key) ? funcall1(key, x2) : x2;
	if (!TRUEP(funcall2(pred, e2, e1))) {
	    set_elt(new_seq, FIX(i), x1);
	    i1++;
	}
	else {
	    set_elt(new_seq, FIX(i), x2);
	    i2++;
	}
    }
    if (i1 < len1) {
	while (i1 < len1) {
	    set_elt(new_seq, FIX(i), elt(seq1, FIX(i1)));
	    i1++;
	    i++;
	}
    }
    else {
	while (i2 < len2) {
	    set_elt(new_seq, FIX(i), elt(seq2, FIX(i2)));
	    i2++;
	    i++;
	}
    }
    RESTORE_STACK();
    return VALUES_1(new_seq);
}

