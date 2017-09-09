/*
 * commonp.c -  Chestnut Run-Time Library entry for function commonp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_warn_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_warn_fptr) ();

#endif




/*ARGSUSED*/
Object commonp (object)
    Object object;
{
    Declare_local_temp;
    warn(1, "X3J13 voted in March 1989 (COMMON-TYPE) to remove the predicate commonp (and the type common) from the language.");
    return VALUES_1(T);  /* future: typep(object, Qcommon) */
}
