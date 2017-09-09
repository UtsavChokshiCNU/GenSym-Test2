/*
 * immedite.c -  Chestnut Run-Time Library entry for function immediate
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern char *SI_string_base(Object o);

#else

extern char *SI_string_base();

#endif




Object lchar (str, index)  /* need immediate (string or result) versions? */
    Object str;
    Object index;
{
    Declare_local_temp;
    /* future: handle displaced strings */
    Object result;

    result = CHAR(str, index);
    return VALUES_1(result);
}
