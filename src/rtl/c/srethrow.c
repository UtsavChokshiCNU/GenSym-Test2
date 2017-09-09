/*
 * srethrow.c -  Chestnut Run-Time Library entry for function SI_re_throw
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Catch_frame *SI_Catch_stack;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_restore_values(void);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_restore_values();

#endif




/* This is invoked when continuing from an unwind_protect.  It's
 * similar to the above except that we have to worry about
 * unstacking the return values instead of stacking them.
 * All values are on the stack (SAVE_VALUES) as this is entered.
 *
 * The return type is int instead of void because the call occurs
 * in a conditional expression, and conditional expressions can't
 * have type void.
 */

extern void SI_unbind_and_jump();

long SI_re_throw ()
{
    Object first_value, tag = STACK_REF(-1);  /* saved tag is left on stack */
    SI_Catch_frame *cf, *cf1;

    for (cf = SI_Catch_stack; cf; cf = cf->link)
	if (cf->tag == tag) {
	    /* No more UWP's; complete the throw */
	    /* stack:  [bottom ... 1value 2value ... tag]  */
	    STACK_POP();  /* remove saved tag */
	    first_value = RESTORE_VALUES(); /* remove ALL values */
	    /* Restore stack ptr *after* popping off the values */
	    Stack = cf->saved_stack_top;
	    /* at this point only the first value has to be onto the stack */
	    STACK_PUSH(first_value);
	    SI_unbind_and_jump(cf);
	    /*NOTREACHED*/
	}
	else if (cf->tag == SI_UNWIND_PROTECT_MARKER)
	    for (cf1 = cf->link; cf1; cf1 = cf1->link)
		if (cf1->tag == tag) {
		    /* Continue throwing across further UWP's */
		    cf->tag = SI_UNINITIALIZED_MARKER;  /* Mark as unwinding */
		    SI_unbind_and_jump(cf);
		    /*NOTREACHED*/
		}
    error(2, "internal error in SI_re_throw!  Failed to find catch for tag ~S",
	  tag);
    /*NOTREACHED*/
    return 0L;
}
