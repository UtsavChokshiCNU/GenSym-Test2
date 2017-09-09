/*
 * functinp.c -  Chestnut Run-Time Library entry for function functionp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/* According to CLtL I, symbols always answer true to FUNCTIONP.
   According to CLtL II, symbols never answer true to FUNCTIONP, which
   makes FUNCTIONP the same as (TYPEP x 'FUNCTION). */

Object functionp (object)
    Object object;
{
    Declare_local_temp;
    return VALUES_1((COMPILED_FUNCTION_P(object) || SYMBOLP(object))
		    ? T : NIL);
}
