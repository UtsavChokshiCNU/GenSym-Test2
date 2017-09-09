/*
 * smkerryn.c -  Chestnut Run-Time Library entry for function SI_make_array_n
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kadjustable;
extern Object Kdisplaced_index_offset;
extern Object Kdisplaced_to;
extern Object Kelement_type;
extern Object Kfill_pointer;
extern Object Kinitial_contents;
extern Object Kinitial_element;

#if SI_USE_PROTOTYPES

extern Object SI_obtain_rest_list(long rest_position, long arg_position, long nargs, va_list *ap);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object SI_obtain_rest_list();
extern Object make_array();

#endif




/*VARARGS*/
Object SI_make_array_n varargs_1(int, n)
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
    BEGIN_ARGS(n);
        REQUIRED_ARGS_1(r1);
        KEYWORD_ARGS_7(Kelement_type, k1, Kinitial_element, k2, Kinitial_contents, k3, Kadjustable, k4, Kfill_pointer, k5, Kdisplaced_to, k6, Kdisplaced_index_offset, k7);
    END_ARGS();
    return make_array(r1, k1, k2, k3, k4, k5, k6, k7);
}
