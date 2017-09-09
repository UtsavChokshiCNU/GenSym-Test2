/*
 * sinpckgn.c -  Chestnut Run-Time Library entry for function SI_in_package_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Knicknames;
extern Object Kuse;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object in_package(Object pkg_name, Object nicknames, Object uses);

#else

extern Object SI_obtain_rest_list();
extern Object in_package();

#endif





/*VARARGS*/
Object SI_in_package_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_2(Knicknames, k1, Kuse, k2);
    END_ARGS();
    return in_package(r1, k1, k2);
}
