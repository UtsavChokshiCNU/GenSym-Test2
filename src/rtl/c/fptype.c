/*
 * fptype.c -  Chestnut Run-Time Library entry for function foreign_pointer_type
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

Object foreign_pointer_type(foreign_pointer)
    Object foreign_pointer;
{
  return VALUES_1(FOREIGN_POINTER_TYPE(foreign_pointer));
}
