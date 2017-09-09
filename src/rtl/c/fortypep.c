/*
 * fortypep.c -  Chestnut Run-Time Library entry for function foreign_type_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qforeign_type;


Object foreign_type_p(foreign_type)
    Object foreign_type;
{
  return VALUES_1(FOREIGN_TYPE_P(foreign_type) ?
		  T : NIL);
}
