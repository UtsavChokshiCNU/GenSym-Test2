/*
 * isngsng.c -  Chestnut Run-Time Library entry for function istring_to_string
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object imake_duplicate_string(char *oldstring);

#else

extern Object imake_duplicate_string();

#endif




/* Coerce a C string to a Lisp string, without copying contents
   (cf. imake_duplicate_string) */

Object istring_to_string (istring)
    char *istring;
{
    Declare_local_temp;
    return imake_duplicate_string(istring);
}
