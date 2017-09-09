/*
 * sreducen.c -  Chestnut Run-Time Library entry for function SI_reduce_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kend;
extern Object Kfrom_end;
extern Object Kinitial_value;
extern Object Kstart;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object reduce(Object function, Object sequence, Object from_end, Object lstart, Object lend, Object initial_value);

#else

extern Object SI_obtain_rest_list();
extern Object reduce();

#endif




/*VARARGS*/
Object SI_reduce_n varargs_1(int, n)
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
        KEYWORD_ARGS_4(Kfrom_end, k1, Kstart, 
		       k2, Kend, k3, Kinitial_value, k4);
    END_ARGS();
    return reduce(r1, r2, k1, k2, k3, k4);
}
