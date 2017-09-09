/*
 * spgvbnng.c -  Chestnut Run-Time Library entry for function SI_progv_restore_bindings
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_set_symbol_value_helper(Object symbol, Object value);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_set_symbol_value_helper();

#endif



void SI_progv_restore_bindings (sp)
    Stack_item *sp;
{
    Object sym, oldval, temp = (--sp)->object;
    int count;
    if (!FIXNUMP(temp)) {
	(void)error(1, "progv_restore_bindings: stack seems to be corrupt");
	/*NOTREACHED*/
    }
    count = IFIX(temp);

    /* This routine MUST NOT alter Values_count or the Values[] array. */
    while (count--) {
	oldval = (--sp)->object;
	sym = (--sp)->object;
	if (!SYMBOLP(sym)) {
	    (void)error(1, "progv_restore_bindings: stack seems to be corrupt");
	    /*NOTREACHED*/
	}
	(void)SI_set_symbol_value_helper(sym, oldval);
    }
}
