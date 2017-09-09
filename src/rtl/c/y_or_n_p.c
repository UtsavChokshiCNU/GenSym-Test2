/*
 * y_or_n_p.c -  Chestnut Run-Time Library entry for function y_or_n_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "svargs.h"


#if SI_USE_PROTOTYPES

extern void SI_y_or_n_p_aux(long v, char *format_string, VA_LIST ap);
extern Object SI_y_or_n_p_query(void);

#else

extern void SI_y_or_n_p_aux();
extern Object SI_y_or_n_p_query();

#endif



Object y_or_n_p varargs_2(long, n,  char *, format_string)
{
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object result;

    VA_START(ap,format_string);
    SI_y_or_n_p_aux(n-1,format_string,ap);
    result = SI_y_or_n_p_query();
    VA_END(ap);
    return result;
}
