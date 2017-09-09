/*
 * sreplcen.c -  Chestnut Run-Time Library entry for function SI_replace_n
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
extern Object replace(Object sequence1, Object sequence2, Object lstart1, Object lend1, Object lstart2, Object lend2);

#else

extern Object SI_obtain_rest_list();
extern Object replace();

#endif




/*VARARGS*/
Object SI_replace_n varargs_1(int, n)
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
    return replace(r1, r2, k1, k2, k3, k4);
}
