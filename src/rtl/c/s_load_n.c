/*
 * s_load_n.c -  Chestnut Run-Time Library entry for function SI_load_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kif_does_not_exist;
extern Object Kprint;
extern Object Kverbose;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object load(Object filename, Object verbose, Object printarg, Object if_does_not_exist);

#else

extern Object SI_obtain_rest_list();
extern Object load();

#endif




/*VARARGS*/
Object SI_load_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_3(Kverbose, k1, Kprint, k2, Kif_does_not_exist, k3);
    END_ARGS();
    return load(r1, k1, k2, k3);
}
