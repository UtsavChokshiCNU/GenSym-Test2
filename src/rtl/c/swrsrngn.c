/*
 * swrsrngn.c -  Chestnut Run-Time Library entry for function SI_write_string_n
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
extern Object write_string(Object string, Object output_stream, Object start, Object end);

#else

extern Object SI_obtain_rest_list();
extern Object write_string();

#endif




/*VARARGS*/
Object SI_write_string_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object o1;
    Object k1;
    Object k2;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        OPTIONAL_ARGS_1(o1);
        KEYWORD_ARGS_2(Kstart, k1, Kend, k2);
    END_ARGS();
    return write_string(r1, o1, k1, k2);
}
