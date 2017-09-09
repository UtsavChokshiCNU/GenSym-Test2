/*
 * snbnnjmp.c -  Chestnut Run-Time Library entry for function SI_unbind_and_jump
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Area *Current_area;
extern SI_Area Local_area;
extern TLS SI_Catch_frame *SI_Catch_stack;
extern TLS SI_Frontier_frame *SI_Frontier_stack;
extern TLS SI_Special_frame *SI_Special_stack;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern int SI_gc_count;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern void restore_frontier(SI_Segment *seg, void *frontier);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_set_symbol_field();
extern void restore_frontier();

#endif




/* Common routine for SI_throw and SI_re_throw*/

void SI_unbind_and_jump(cf)
    SI_Catch_frame *cf;
{
    SI_Special_frame *target = cf->saved_special_stack;
    SI_Special_frame *bstack;

    SI_Frontier_frame *ftarget = cf->frontier;
    SI_Frontier_frame *fstack, *factual;
    
    for (bstack = SI_Special_stack; bstack != target; bstack = bstack->link) {
	if (bstack == NULL)
	    error(1,"unwind_and_jump: internal error unbinding specials!");
        if (bstack->location == NULL) 
	    SET_SYMBOL_VALUE(bstack->symbol, bstack->saved_value);
        else
            *(bstack->location) = bstack->saved_value;
    }
    SI_Special_stack = target;

    SI_FLUSH_ALLOC_CACHE();
    Current_area = &Local_area; /* assuming there is currently only one */
    for (factual = NULL, fstack = SI_Frontier_stack;
	 fstack != ftarget;
	 factual = fstack, fstack = fstack->link) {
	if (fstack == NULL)
	    error(1, "unwind_and_jump: internal error while restoring areas!");
    }
    /* restore only the "oldest" saved position in Local area */
    if (factual != NULL) RESTORE_FRONTIER(*factual);

    Current_area = cf->saved_area;
    SI_RELOAD_ALLOC_CACHE();

    SI_Catch_stack = cf->link; /* Redundant (see SI_POP_CATCH) */
    longjmp(cf->g2jmpbuf, 1);
    /*NOTREACHED*/
}

