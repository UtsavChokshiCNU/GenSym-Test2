/*
 * upstpckg.c -  Chestnut Run-Time Library entry for function up_set_package
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

DECLARE_VARIABLE(Package);

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object ifind_package(char *name);
extern Object istring_to_string(char *istring);

#else

extern Object (*SI_error_fptr) ();
extern Object ifind_package();
extern Object istring_to_string();

#endif



/* entry name up_set_package(){}  */
Object SET_PACKAGE (string)
    char *string;
{
    Object pack = ifind_package(string);

    if (pack == NIL)
	error(2, "set_package: no such package - ~a", 
	      istring_to_string(string));
    else
	Package = pack;
    return VALUES_0();
}

