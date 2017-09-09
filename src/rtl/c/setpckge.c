/*
 * setpckge.c -  Chestnut Run-Time Library entry for function set_package
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
extern Object find_package(Object);

#else

extern Object (*SI_error_fptr) ();
extern Object find_package();

#endif



Object set_package (string)
    Object string;
{
    /* Probably the wrong semantics */
    Object pack = find_package(string);

    if (pack == NIL)
	error(2, "set_package: no such package - ~a", string);
    else
	Package = pack;
    return VALUES_0();
}
