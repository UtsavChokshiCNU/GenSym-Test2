/*
 * sprsngrn.c -  Chestnut Run-Time Library entry for function SI_parse_integer_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kjunk_allowed;
extern Object Kradix;
extern Object Kstart;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object parse_integer(Object string, Object start, Object end, Object radix, Object junk_allowed);

#else

extern Object SI_obtain_rest_list();
extern Object parse_integer();

#endif




/*VARARGS*/
Object SI_parse_integer_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_4(Kstart, k1, Kend, k2, Kradix, k3, Kjunk_allowed, k4);
    END_ARGS();
    return parse_integer(r1, k1, k2, k3, k4);
}
