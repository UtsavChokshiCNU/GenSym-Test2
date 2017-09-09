/*
 * spnmngn.c -  Chestnut Run-Time Library entry for function SI_parse_namestring_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kjunk_allowed;
extern Object Kstart;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object parse_namestring(Object thing, Object host, Object defaults, Object start, Object end, Object junk_allowed);

#else

extern Object SI_obtain_rest_list();
extern Object parse_namestring();

#endif




/*VARARGS*/
Object SI_parse_namestring_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    Object o1, o2;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        /* OPTIONAL_ARGS_2(o1, o2); - broken */
        XOPTIONAL_ARG(o1);
        XOPTIONAL_ARG(o2);
        KEYWORD_ARGS_3(Kstart, k1, Kend, k2, Kjunk_allowed, k3);
    END_ARGS();
    return parse_namestring(r1, o1, o2, k1, k2, k3);
}
