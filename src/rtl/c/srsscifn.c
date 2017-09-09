/*
 * srsscifn.c -  Chestnut Run-Time Library entry for function SI_rassoc_if_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kkey;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object rassoc_if(Object pred, Object a_list, Object key);

#else

extern Object SI_obtain_rest_list();
extern Object rassoc_if();

#endif




/*VARARGS*/
Object SI_rassoc_if_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_1(Kkey, k1);
    END_ARGS();
    return rassoc_if(r1, r2, k1);
}
