/*
 * subseq.c -  Chestnut Run-Time Library entry for function subseq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object array_element_type(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_string(Object size, Object initial_element);
extern Object ncons1(Object a);
extern Object replace(Object sequence1, Object sequence2, Object lstart1, Object lend1, Object lstart2, Object lend2);

#else

extern char *SI_istring();
extern Object array_element_type();
extern Object make_array();
extern Object make_string();
extern Object ncons1();
extern Object replace();

#endif



extern Object SI_init_sequence_fn();

/* SUBSEQ:  if sequence is a vector,
 * then create a new vector and copy the contents.  Otherwise, can assume
 * LISTP(sequence), i.e. a CONS or NIL
 * Routine assumes that sequence does not end with a dotted atom.
 * Position to item#start of sequence
 */
/* &optional 2 1 */
Object subseq (sequence, lstart, lend)
    Object sequence, lstart, lend;
{
    Declare_local_temp;
    long i, len, start, end;
    Object last_cell, new_cell, result;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(sequence);
    PROTECTI_3(last_cell,new_cell,result);
    /* *** just pass supplied 'lend' to SI_init_sequence_fn */
    sequence = SI_init_sequence_fn(sequence, lstart, lend, &start, &end);
    len = end - start;
    len = MAX(0L, len);

    if (STRINGP(sequence)) {
	/* [Efficiency hack?] */
	result = make_string(FIX(len), KOPT);
	(void)strncpy(ISTRING(result),ISTRING(sequence)+start, (int) len);
	ISTRING(result)[len] = '\0';
	RESTORE_STACK();
	return VALUES_1(result);
    }
    else if (VECTORP(sequence)) {
	result = make_array(FIX(len), array_element_type(sequence),
			    KOPT, KOPT, KOPT, KOPT, KOPT, KOPT);
	RESTORE_STACK();
	return(replace(result, sequence, ZERO, 
		       FIX(len), FIX(start), FIX(end)));
    }

    /* must be a LIST */
    if (sequence == NIL) {
	RESTORE_STACK();
	return VALUES_1(NIL);
    }
    /* start copying; build first cell */
    last_cell = result = ncons1(M_CAR(sequence));
    sequence = M_CDR(sequence);
    for (i = start+1L; TRUEP(sequence) && (!end || (i < end));
	 i++, sequence = M_CDR(sequence)) {
	new_cell = ncons1(M_CAR(sequence));
	RPLACD(last_cell, new_cell);
	last_cell = new_cell;
    }
    /* since using ncons1, must tack NIL onto end; then return */
    RPLACD(last_cell, NIL);
    RESTORE_STACK();
    return VALUES_1(result);
}
