/*
 * scntfntn.c -  Chestnut Run-Time Library entry for function SI_count_if_not_n
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

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object count_if_not(Object test, Object seq, Object from_end, Object lstart, Object lend, Object key);

#else

extern Object SI_obtain_rest_list();
extern Object count_if_not();

#endif




/*VARARGS*/
Object SI_count_if_not_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object r2;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_2(r1, r2);
        KEYWORD_ARGS_4(Kfrom_end, k1, Kstart, k2, Kend, k3, Kkey, k4);
    END_ARGS();
    return count_if_not(r1, r2, k1, k2, k3, k4);
}
