/*
 * sfptype.c -  Chestnut Run-Time Library entry for function set_foreign_pointer_type
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

Object set_foreign_pointer_type(foreign_pointer,new_type)
    Object foreign_pointer,new_type;
{
  FOREIGN_POINTER_TYPE(foreign_pointer) = new_type;
  return VALUES_1(new_type);
}
