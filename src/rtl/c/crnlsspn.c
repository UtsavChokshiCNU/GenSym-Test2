/*
 * crnlsspn.c -  Chestnut Run-Time Library entry for function char_not_lesspn
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object char_not_lessp(Object a, Object b);

#else

extern Object char_not_lessp();

#endif


#include "chars.h"

Object char_not_lesspn varargs_1(int, n)
{
    va_list ap;
    Object result;

    SI_va_start(ap,n);
    result = SI_char_relopn(char_not_lessp, n, ap);
    va_end(ap);
    return result;
}
