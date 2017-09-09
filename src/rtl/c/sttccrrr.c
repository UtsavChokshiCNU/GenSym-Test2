/*
 * sttccrrr.c -  Chestnut Run-Time Library entry for function STATIC_CHAR_ARRAY
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qchar;

#if SI_USE_PROTOTYPES

extern Object SI_make_static_array(Object type, long n, va_list ap);

#else

extern Object SI_make_static_array();

#endif


#include "stat_arr.h"


Object STATIC_CHAR_ARRAY varargs_1(int, n)
{
    MAKE_STATIC_ARRAY(Qchar,n);
}
