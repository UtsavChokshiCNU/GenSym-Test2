/*
 * mdcmbnn.c -  Chestnut Run-Time Library entry for function method_combination_error
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
/* entry name: method_combination_error(){} */
/*ARGSUSED*//*VARARGS*/DUMMY_V(method_combination_error)

