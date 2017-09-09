/*
 * slplcsn.c -  Chestnut Run-Time Library entry for function SI_delete_duplicates_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kfrom_end;
extern Object Kkey;
extern Object Kstart;
extern Object Ktest_not;
extern Object Ktest;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object delete_duplicates(Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object key);

#else

extern Object SI_obtain_rest_list();
extern Object delete_duplicates();

#endif




/*VARARGS*/
Object SI_delete_duplicates_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    Object k5;
    Object k6;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_6(Kfrom_end, k1, Ktest, k2, Ktest_not, k3, Kstart, k4, Kend, k5, Kkey, k6);
    END_ARGS();
    return delete_duplicates(r1, k1, k2, k3, k4, k5, k6);
}
