/*
 * numbers.h - macros and globals for numeric fumctions
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#ifndef HAVE_AINT
/* There must be a better way to do this!  Will modf do the trick? */
#define aint(x)   ((x) < 0 ? -floor(-x) : floor(x))
/* This isn't correct.  Fix it later. */
#define rint(x)	  ceil((x) - 0.5)
#endif

extern Object xbignum_normalize();
extern Object make_ratio();
extern Object double_to_integer();


extern Object SI_Float_zero;
extern Object SI_Float_one;
extern Object SI_Float_negative_one;

extern int     SI_gc_unsafe = 0;
extern jmp_buf SI_restart_unsafe;





