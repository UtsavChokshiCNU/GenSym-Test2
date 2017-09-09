/*
 * tlllcbl.c -  Chestnut Run-Time Library entry for function total_memory_allocatable
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS SI_Long L_temp;

#if SI_USE_PROTOTYPES

extern Object clong_to_bignum(SI_Long a);

#else

extern Object clong_to_bignum();

#endif


#ifdef unix

Object total_memory_allocatable()
{
    Declare_local_temp;
    Object temp1;
    Declare_stack_pointer;
    extern unsigned long haumuch();

    SAVE_STACK();
    PROTECTI_1(temp1);
    temp1 = T_MAKE_INTEGER(haumuch());
    RESTORE_STACK();
    return(VALUES_1(temp1));
}

/* Find out how much is allocatable by actually trying to allocate it.
   Do a binary search to hone in on the exact amount.  This is rather
   dependent on the crufty Unix memory model (sbrk, brk).  Your advice
   on how to implement this on more principled operating systems (VMS,
   MSDOS, ...) is welcome.  Does VMS really implement brk() and
   sbrk()? */

/* On the hp 9000/800, sbrk() is declared (incompatibly?) in unistd.h,
   which is included by runtime.h. */


#if !defined(hp9000s800) && !defined(Platform_Solaris) && !defined(hp9000s300) && !defined(nec) && !defined(__osf__) && !defined(_IBMR2) && !defined(Platform_Linux)
extern caddr_t brk();
#else
extern int brk();
#endif

#define FUDGE 10000		/* About 17 iterations */
#define MARGIN 100000		/* Experimentally determined */

unsigned long haumuch() {
    caddr_t the_end, lower, upper, new;

    the_end = sbrk(0);

    lower = the_end;
    upper = (caddr_t)(1 << 30);

    while ((char *)lower + 50 < (char *)upper) {
	new = (caddr_t)(((unsigned long)upper >> 1)
			+ ((unsigned long)lower >> 1));
	if (brk(new) >= 0)
	    lower = new;
	else
	    upper = new;
    }

    if (brk(the_end) < 0)
	fprintf(stderr, "Lossage!\n");

    return (char *)lower - (char *)the_end - MARGIN;
}

#endif
