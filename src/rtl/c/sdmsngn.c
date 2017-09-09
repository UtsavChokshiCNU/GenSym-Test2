/*
 * sdmsngn.c -  Chestnut Run-Time Library entry for function SI_read_from_string_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kpreserve_whitespace;
extern Object Kstart;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object read_from_string(Object string, Object eof_error_p, Object eof_value, Object start, Object end, Object preserve_whitespace);

#else

extern Object SI_obtain_rest_list();
extern Object read_from_string();

#endif




/*VARARGS*/
Object SI_read_from_string_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object o1;
    Object o2;
    Object k1;
    Object k2;
    Object k3;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        XOPTIONAL_ARG(o1);
        XOPTIONAL_ARG(o2);
        KEYWORD_ARGS_3(Kstart, k1, Kend, k2, Kpreserve_whitespace, k3);
    END_ARGS();
    return read_from_string(r1, o1, o2, k1, k2, k3);
}
