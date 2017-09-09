/*
 * defftp.c -  Chestnut Run-Time Library entry for function defined_foreign_type_p
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object get_foreign_type(Object,Object);

#else

extern Object get_foreign_type();

#endif



Object defined_foreign_type_p(foreign_type_name)
    Object foreign_type_name;
{
  return get_foreign_type(foreign_type_name,NIL);
}

