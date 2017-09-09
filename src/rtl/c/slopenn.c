/*
 * slopenn.c -  Chestnut Run-Time Library entry for function SI_lopen_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kdirection;
extern Object Kelement_type;
extern Object Kif_does_not_exist;
extern Object Kif_exists;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object lopen(Object filename, Object direction, Object element_type, Object if_exists, Object if_does_not_exist);

#else

extern Object SI_obtain_rest_list();
extern Object lopen();

#endif




/*VARARGS*/
Object SI_lopen_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_4(Kdirection, k1, Kelement_type, k2, Kif_exists, k3, Kif_does_not_exist, k4);
    END_ARGS();
    return lopen(r1, k1, k2, k3, k4);
}
