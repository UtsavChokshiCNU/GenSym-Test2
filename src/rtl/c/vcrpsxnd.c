/*
 * vcrpsxnd.c -  Chestnut Run-Time Library entry for function vector_push_extend
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object adjust_array(Object array, Object new_dimensions, Object element_type, Object initial_element, Object initial_contents, Object fill_pointer, Object displaced_to, Object displaced_index_offset);
extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object (*SI_error_fptr) ();
extern Object adjust_array();
extern Object do_setf_aref();

#endif




Object vector_push_extend (new_element, vector, extension)
    Object new_element, vector, extension;
{
    Declare_local_temp;
    Object fillptr, total_size;
    Declare_stack_pointer;

    if (!ARRAY_HAS_FILL_POINTER_P(vector))
	return error(2, "vector_push_extend: invalid argument - ~S", vector);

    fillptr = SI_GENERAL_VECTOR_FILL_POINTER(vector);
    total_size = FIX(SI_GENERAL_VECTOR_TOTAL_SIZE(vector));
    SAVE_STACK();
    PROTECT_3(new_element, vector, extension);
    if (FIXNUM_GE(fillptr, total_size)) {
	if (UNSUPPLIED_P(extension))
	    extension = FIX(128L);
	vector = adjust_array(vector,
			      FIXNUM_ADD(total_size, extension),
			      KOPT, KOPT, KOPT, KOPT, KOPT, KOPT);
    }
    (void)do_setf_aref(vector, (SI_Dimension)IFIX(fillptr), new_element);
    SET_FILL_POINTER(vector, FIXNUM_ADD1(fillptr));
    RESTORE_STACK();
    return VALUES_1(fillptr);
}
