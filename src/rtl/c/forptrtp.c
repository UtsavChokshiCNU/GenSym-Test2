/*
 * foreign_pointer_p.c -  Chestnut Run-Time Library entry for function foreign_pointer_type_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

Object foreign_pointer_type_p(foreign_pointer)
    Object foreign_pointer;
{
  return (FOREIGN_POINTER_TYPE_P(foreign_pointer) ?
	  T : NIL);
}
