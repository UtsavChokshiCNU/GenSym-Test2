/*
 * ftmod.c -  Chestnut Run-Time Library entry for function foreign_type_modulus
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qforeign_type;

#if SI_USE_PROTOTYPES

extern Object get_foreign_type(Object,Object);

#else

extern Object get_foreign_type();

#endif



Object foreign_type_modulus(foreign_type)
    Object foreign_type;
{
  unsigned short modulus;

  modulus = (unsigned short)FOREIGN_TYPE_MODULUS(FOREIGN_TYPE(foreign_type));
  return VALUES_1(UNSIGNED_SHORT_TO_INTEGER(modulus));
}
