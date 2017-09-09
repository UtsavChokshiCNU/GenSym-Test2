/*
 * setaref2.c -  Chestnut Run-Time Library entry for function set_aref2
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




Object set_aref2(a, i1, i2, v)
  Object a, i1, i2, v;
{ return do_setf_aref(a, (SI_Dimension)ROW_MAJOR_INDEX_2(a, i1, i2), v); }
