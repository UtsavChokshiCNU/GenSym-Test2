/*
 * nsrngpcs.c -  Chestnut Run-Time Library entry for function nstring_upcase
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

#if SI_USE_PROTOTYPES

extern char *SI_string_base(Object o);
extern long ilength(Object sequence);
extern Object string(Object);

#else

extern char *SI_string_base();
extern long ilength();
extern Object string();

#endif


Object nstring_upcase (str, start, end)
    Object str;
    Object start, end;
{
    Declare_local_temp;
    char *a, c;
    long istart, iend;

    str = STRING(str);
    a = SI_string_base(str);

    istart = UNSUPPLIED_P(start) ? 0 : IFIX(start);
    iend = (!UNSUPPLIED_P(end) && TRUEP(end)) ? IFIX(end) : ilength(str);

    while (istart < iend) {
	c = *(a+istart);
	*(a+istart) = TOUPPER(c);
	istart++;
    }
    return VALUES_1(str);
}
