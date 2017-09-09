/*
 * sstrngln.c -  Chestnut Run-Time Library entry for function SI_string_le_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend1;
extern Object Kend2;
extern Object Kstart1;
extern Object Kstart2;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object string_le(Object string1, Object string2, Object start1, Object end1, Object start2, Object end2);

#else

extern Object SI_obtain_rest_list();
extern Object string_le();

#endif




/*VARARGS*/
Object SI_string_le_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_4(Kstart1, k1, Kend1, k2, Kstart2, k3, Kend2, k4);
    END_ARGS();
    return string_le(r1, r2, k1, k2, k3, k4);
}
