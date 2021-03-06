/*
 * strngpcs.c -  Chestnut Run-Time Library entry for function string_upcase
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object make_duplicate_string(Object oldstring);
extern Object nstring_upcase(Object str, Object start, Object end);
extern Object string(Object);

#else

extern Object make_duplicate_string();
extern Object nstring_upcase();
extern Object string();

#endif




Object string_upcase (str, start, end)
    Object str, start, end;
{
    return nstring_upcase(make_duplicate_string(STRING(str)),start,end);
}
