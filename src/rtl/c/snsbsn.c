/*
 * snsbsn.c -  Chestnut Run-Time Library entry for function SI_nsubstitute_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kcount;
extern Object Kend;
extern Object Kfrom_end;
extern Object Kkey;
extern Object Kstart;
extern Object Ktest_not;
extern Object Ktest;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object nsubstitute(Object newitem, Object olditem, Object seq, Object from_end, Object test, Object test_not, Object lstart, Object lend, Object lcount, Object key);

#else

extern Object SI_obtain_rest_list();
extern Object nsubstitute();

#endif




/*VARARGS*/
Object SI_nsubstitute_n varargs_1(long, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object r3;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    Object k5;
    Object k6;
    Object k7;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_3(r1, r2, r3);
        KEYWORD_ARGS_7(Kfrom_end, k1, Ktest, k2, Ktest_not, k3, Kstart, k4, Kend, k5, Kcount, k6, Kkey, k7);
    END_ARGS();
    return nsubstitute(r1, r2, r3, k1, k2, k3, k4, k5, k6, k7);
}
