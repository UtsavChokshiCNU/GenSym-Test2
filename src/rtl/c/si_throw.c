/*
 * si_throw.c -  Chestnut Run-Time Library entry for function SI_throw
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
extern void SI_save_values(void);

#else

extern Object (*SI_error_fptr) ();
extern void SI_save_values();

#endif



extern void SI_unbind_and_jump();

/* Throw */

/* Initiate a THROW.
 *
 * First scan through the catch stack looking for the
 * matching CATCH, and also looking to see whether there are any
 * UNWIND-PROTECTs that have to be executed.  If there are, then we
 * must save the tag on the stack so that it can
 * rethrow, and the return values in the actual target frame so rethrow
 * can retrieve them.
 *
 * Once we've figured out where we're going, restore the special binding
 * stack and local variable frame stack pointers, and do the longjmp.
 */

Object SI_throw (tag, firstval)
    Object tag, firstval;
{
    SI_Catch_frame *cf, *cf1;

    for (cf = SI_Catch_stack; cf; cf = cf->link)
	if (cf->tag == tag) {
	    /* Simple throw with no intervening UWP's */
	    Stack = cf->saved_stack_top;
	    /* a catcher can find the first value onto the stack;
	     * also, a catcher is responsible for removing it */
	    STACK_PUSH(firstval);
	    SI_unbind_and_jump(cf);
	    /*NOTREACHED*/
	}
	else if (cf->tag == SI_UNWIND_PROTECT_MARKER)
	    for (cf1 = cf->link; cf1; cf1 = cf1->link)
		if (cf1->tag == tag) {
		    /* Throw across UWP to a tag for which there's a catch */
		    SAVE_VALUES(firstval); /* Push ALL values onto stack */
		    cf->tag = SI_UNINITIALIZED_MARKER;  /* Mark as unwinding */
		    STACK_PUSH(tag);       /* Save old tag */
		    SI_unbind_and_jump(cf);
		    /*NOTREACHED*/
		}
    error(2, "throw: failed to find catch for tag ~S", tag);
    /*NOTREACHED*/
	return NULL; //this function return somthing
}
