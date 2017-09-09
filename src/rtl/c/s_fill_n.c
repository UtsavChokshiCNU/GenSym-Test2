/*
 * s_fill_n.c -  Chestnut Run-Time Library entry for function SI_fill_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kstart;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object fill(Object seq, Object item, Object lstart, Object lend);

#else

extern Object SI_obtain_rest_list();
extern Object fill();

#endif




/*VARARGS*/
Object SI_fill_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    Object k2;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_2(Kstart, k1, Kend, k2);
    END_ARGS();
    return fill(r1, r2, k1, k2);
}
