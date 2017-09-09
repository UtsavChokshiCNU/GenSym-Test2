/*
 * namechar.c -  Chestnut Run-Time Library entry for function name_char
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern Object iname_char(char *iname);

#else

extern char *SI_istring();
extern Object iname_char();

#endif


#include "chars.h"

/* Find a character with the given name, e.g. "Newline" => #\newline */

Object name_char(name)
    Object name;
{
    Declare_local_temp;
    return VALUES_1(iname_char(ISTRING(name)));
}
