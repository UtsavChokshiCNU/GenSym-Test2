/*
 * slclosen.c -  Chestnut Run-Time Library entry for function SI_lclose_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kabort;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object lclose(Object stream, Object abort);

#else

extern Object SI_obtain_rest_list();
extern Object lclose();

#endif




/*VARARGS*/
Object SI_lclose_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_1(Kabort, k1);
    END_ARGS();
    return lclose(r1, k1);
}
