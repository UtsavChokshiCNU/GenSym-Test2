/*
 * setaref0.c -  Chestnut Run-Time Library entry for function set_aref0
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




Object set_aref0(arr, new_elem)
    Object arr, new_elem;
{
    return do_setf_aref(arr,
			(SI_Dimension)ROW_MAJOR_INDEX_0(arr),
			new_elem);
}
