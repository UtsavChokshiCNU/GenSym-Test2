/*
 * setaref7.c -  Chestnut Run-Time Library entry for function set_aref7
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object do_setf_aref(Object arr, SI_Dimension i, Object elem);

#else

extern Object do_setf_aref();

#endif




Object set_aref7(arr, s1, s2, s3, s4, s5, s6, s7, new_elem)
    Object arr, new_elem;
    Object s1, s2, s3, s4, s5, s6, s7;
{
    return(do_setf_aref(arr,
			(SI_Dimension)ROW_MAJOR_INDEX_7(arr, s1, s2, s3, s4, s5, s6, s7),
			new_elem));
}
