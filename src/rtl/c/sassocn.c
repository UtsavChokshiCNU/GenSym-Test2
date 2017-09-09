/*
 * sassocn.c -  Chestnut Run-Time Library entry for function SI_assoc_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kkey;
extern Object Ktest_not;
extern Object Ktest;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object assoc(Object item, Object a_list, Object test, Object test_not, Object key);

#else

extern Object SI_obtain_rest_list();
extern Object assoc();

#endif




/*VARARGS*/
Object SI_assoc_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    Object k2;
    Object k3;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_3(Ktest, k1, Ktest_not, k2, Kkey, k3);
    END_ARGS();
    return assoc(r1, r2, k1, k2, k3);
}
