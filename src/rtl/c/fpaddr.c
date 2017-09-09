/*
 * fpaddr.c -  Chestnut Run-Time Library entry for function foreign_pointer_address
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern bignum_type unsigned_long_to_bignum (SI_Ulong);

#else

extern bignum_type unsigned_long_to_bignum ();

#endif



Object foreign_pointer_address(foreign_pointer)
    Object foreign_pointer;
{
  SI_Ulong address;

  address = FOREIGN_POINTER_ADDRESS(foreign_pointer);
  return VALUES_1(UNSIGNED_LONG_TO_INTEGER(address));
}
