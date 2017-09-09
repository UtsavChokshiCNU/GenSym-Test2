/*
 * cnsnlfls.c -  Chestnut Run-Time Library entry for function constantly_false
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


/*ARGSUSED*/
Object constantly_false varargs_1(int, n)
{
    Declare_local_temp;
  return VALUES_1(NIL); 
}
