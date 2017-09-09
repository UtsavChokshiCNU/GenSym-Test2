/*
 * smsmtchn.c -  Chestnut Run-Time Library entry for function SI_mismatch_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend1;
extern Object Kend2;
extern Object Kfrom_end;
extern Object Kkey;
extern Object Kstart1;
extern Object Kstart2;
extern Object Ktest_not;
extern Object Ktest;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object mismatch(Object seq1, Object seq2, Object from_end, Object test, Object test_not, Object key, Object lstart1, Object lstart2, Object lend1, Object lend2);

#else

extern Object SI_obtain_rest_list();
extern Object mismatch();

#endif




/*VARARGS*/
Object SI_mismatch_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    Object k5;
    Object k6;
    Object k7;
    Object k8;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_8(Kfrom_end, k1, Ktest, k2, Ktest_not, k3, Kkey, k4, Kstart1, k5, Kstart2, k6, Kend1, k7, Kend2, k8);
    END_ARGS();
    return mismatch(r1, r2, k1, k2, k3, k4, k5, k6, k7, k8);
}
