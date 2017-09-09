/*
 * srngcplz.c -  Chestnut Run-Time Library entry for function string_capitalize
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object make_duplicate_string(Object oldstring);
extern Object nstring_capitalize(Object str, Object start, Object end);
extern Object string(Object);

#else

extern Object make_duplicate_string();
extern Object nstring_capitalize();
extern Object string();

#endif




Object string_capitalize (str, start, end)
    Object str;
    Object start, end;
{
    return nstring_capitalize(make_duplicate_string(STRING(str)),
			      start, end);
}
