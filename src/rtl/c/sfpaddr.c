/*
 * sfpaddr.c -  Chestnut Run-Time Library entry for function set_foreign_pointer_address
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern SI_Ulong integer_to_unsigned_long(Object n);

#else

extern SI_Ulong integer_to_unsigned_long();

#endif



Object set_foreign_pointer_address(foreign_pointer,new_address)
    Object foreign_pointer,new_address;
{
  FOREIGN_POINTER_ADDRESS(foreign_pointer) = 
    INTEGER_TO_UNSIGNED_LONG(new_address);
  return VALUES_1(new_address);
}
