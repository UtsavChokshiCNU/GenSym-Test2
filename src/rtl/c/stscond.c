/*
 * stscond.c -  Chestnut Run-Time Library entry for function set_second
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif


#include "dummy.h"

/* not yet implemented */
/* entry name: set_second(){} */
/*ARGSUSED*/DUMMY_2(set_second)

