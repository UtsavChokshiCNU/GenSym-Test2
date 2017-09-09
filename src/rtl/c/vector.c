/*
 * vector.c -  Chestnut Run-Time Library entry for function vector
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object do_setf_aref();
extern Object make_array();

#endif




Object vector varargs_1(int, n)
{
    va_list ap;
    SI_Dimension i;
    Object vector_var;

    SI_va_start(ap,n);
    vector_var = make_array(FIX(n),T,KOPT,KOPT,KOPT,KOPT,KOPT,KOPT);
    for (i = 0; i < n; i++)
	(void)do_setf_aref(vector_var,i,va_arg(ap,Object));
    va_end(ap);
    return vector_var;
}
