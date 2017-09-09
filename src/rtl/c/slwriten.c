/*
 * slwriten.c -  Chestnut Run-Time Library entry for function SI_lwrite_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Karray;
extern Object Kbase;
extern Object Kcase;
extern Object Kcircle;
extern Object Kescape;
extern Object Kgensym;
extern Object Klength;
extern Object Klevel;
extern Object Kpretty;
extern Object Kradix;
extern Object Kstream;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object lwrite(Object object, Object stream, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);

#else

extern Object SI_obtain_rest_list();
extern Object lwrite();

#endif




/*VARARGS*/
Object SI_lwrite_n varargs_1(int, n)
{
    XDeclare_varargs;
    Object r1;
    Object k1;
    Object k2;
    Object k3;
    Object k4;
    Object k5;
    Object k6;
    Object k7;
    Object k8;
    Object k9;
    Object k10;
    Object k11;
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_11(Kstream, k1, Kescape, k2, Kradix, k3, Kbase, k4, Kcircle, k5, Kpretty, k6, Klevel, k7, Klength, k8, Kcase, k9, Kgensym, k10, Karray, k11);
    END_ARGS();
    return lwrite(r1, k1, k2, k3, k4, k5, k6, k7, k8, k9, k10, k11);
}
