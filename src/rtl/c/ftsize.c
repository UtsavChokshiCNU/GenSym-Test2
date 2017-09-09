/*
 * ftsize.c -  Chestnut Run-Time Library entry for function foreign_type_size
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
extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern Object get_foreign_type();
extern bignum_type unsigned_long_to_bignum ();

#endif



Object foreign_type_size(foreign_type)
    Object foreign_type;
{
  SI_Ulong size;

  size = FOREIGN_TYPE_SIZE(FOREIGN_TYPE(foreign_type));
  return VALUES_1(UNSIGNED_LONG_TO_INTEGER(size));
}
