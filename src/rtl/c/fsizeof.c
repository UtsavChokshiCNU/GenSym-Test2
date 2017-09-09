/*
 * fsizeof.c -  Chestnut Run-Time Library entry for function foreign_size_of
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qforeign_type;
extern Object Qpointer_foreign_type;

#if SI_USE_PROTOTYPES

extern Object get_foreign_type(Object,Object);
extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern Object get_foreign_type();
extern bignum_type unsigned_long_to_bignum ();

#endif



Object foreign_size_of(foreign_pointer_or_type)
    Object foreign_pointer_or_type;
{
  SI_Ulong size;

  if(FOREIGN_POINTER_TYPE_P(foreign_pointer_or_type))
    {
      foreign_pointer_or_type = FOREIGN_POINTER_TYPE(foreign_pointer_or_type);
      if(POINTER_FOREIGN_TYPE_P(foreign_pointer_or_type))
	foreign_pointer_or_type =
	  POINTER_FOREIGN_TYPE_TO_TYPE(foreign_pointer_or_type);
    }
  size = FOREIGN_TYPE_SIZE(FOREIGN_TYPE(foreign_pointer_or_type));
  return UNSIGNED_LONG_TO_INTEGER(size);
}

