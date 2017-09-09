/*
 * yesornop.c -  Chestnut Run-Time Library entry for function yes_or_no_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
#include "svargs.h"


#if SI_USE_PROTOTYPES

extern char *SI_istring(Object o);
extern void SI_y_or_n_p_aux(long v, char *format_string, VA_LIST ap);
extern Object SI_yes_or_no_p_query(void);

#else

extern char *SI_istring();
extern void SI_y_or_n_p_aux();
extern Object SI_yes_or_no_p_query();

#endif


/* &optional 0 1 */
Object yes_or_no_p varargs_2(long, n,  char *, format_string)
{
    Declare_va_stack_pointer;
    VA_LIST ap;
    Object result;

    VA_START(ap,format_string);
    SI_y_or_n_p_aux(n-1,ISTRING(format_string),ap);
    result = SI_yes_or_no_p_query();
    VA_END(ap);
    return result;
}
