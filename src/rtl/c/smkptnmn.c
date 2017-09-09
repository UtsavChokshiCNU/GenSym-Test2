/*
 * smkptnmn.c -  Chestnut Run-Time Library entry for function SI_make_pathname_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kdefaults;
extern Object Kdevice;
extern Object Kdirectory;
extern Object Khost;
extern Object Kname;
extern Object Ktype;
extern Object Kversion;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object make_pathname(Object host, Object device, Object directory, Object name, Object type, Object version, Object defaults);

#else

extern Object SI_obtain_rest_list();
extern Object make_pathname();

#endif




/*VARARGS*/
Object SI_make_pathname_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    Object k5;
    Object k6;
    Object k7;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_0();
        KEYWORD_ARGS_7(Khost, k1, Kdevice, k2, Kdirectory, k3, Kname, k4, Ktype, k5, Kversion, k6, Kdefaults, k7);
    END_ARGS();
    return make_pathname(k1, k2, k3, k4, k5, k6, k7);
}
