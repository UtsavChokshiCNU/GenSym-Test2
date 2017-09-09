/*
 * copy_seq.c -  Chestnut Run-Time Library entry for function copy_seq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object array_element_type(Object);
extern Object copy_list(Object);
extern Object do_aref_1(Object arr, long i);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object length(Object);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object make_duplicate_string(Object oldstring);

#else

extern Object array_element_type();
extern Object copy_list();
extern Object do_aref_1();
extern Object do_setf_aref();
extern Object length();
extern Object make_array();
extern Object make_duplicate_string();

#endif




/* (copy-seq sequence) <=> (subseq sequence 0)... */

Object copy_seq (sequence)
    Object sequence;
{
    Declare_local_temp;
    Object result, size;
    SI_Dimension i, len;
    Declare_stack_pointer;

    if (LISTP(sequence))
	result = copy_list(sequence);
    else if (STRINGP(sequence))
	result = make_duplicate_string(sequence);
    else {
	SAVE_STACK();
	PROTECT_1(sequence);
	PROTECTI_2(result,size);

	size = length(sequence);
	result = make_array(size, array_element_type(sequence),
			    KOPT, KOPT, NIL, NIL, NIL, KOPT);
	len = IFIX(size);

	for (i = 0; i < len; i++)
	    do_setf_aref(result, i, do_aref_1(sequence, (long)i));

	RESTORE_STACK();
    }
    return VALUES_1(result);
}
