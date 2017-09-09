/*
 * swrtstng.c -  Chestnut Run-Time Library entry for function SI_wr_to_stng
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

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object write_to_string(Object object, Object pescape, Object pradix, Object pbase, Object pcircle, Object ppretty, Object plevel, Object plength, Object pcase, Object pgensym, Object parray);

#else

extern Object SI_obtain_rest_list();
extern Object write_to_string();

#endif



/* entry name: SI_wr_to_stng() {} */
/*VARARGS*/
Object SI_write_to_string_n varargs_1(int, n)
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
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_10(Kescape, k1, Kradix, k2, Kbase, k3, Kcircle, k4, Kpretty, k5, Klevel, k6, Klength, k7, Kcase, k8, Kgensym, k9, Karray, k10);
    END_ARGS();
    return write_to_string(r1, k1, k2, k3, k4, k5, k6, k7, k8, k9, k10);
}
