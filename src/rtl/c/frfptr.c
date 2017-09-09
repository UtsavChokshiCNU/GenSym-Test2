/*
 * frfptr.c -  Chestnut Run-Time Library entry for function free_foreign_pointer
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

Object free_foreign_pointer(foreign_pointer)
     Object foreign_pointer;
{
  char *address=(char *)FOREIGN_POINTER_ADDRESS(foreign_pointer);
  
  free((char *)((SI_Ulong)address-
		((SI_Ulong)(address[-2L])+
		 ((SI_Ulong)(address[-1L])<<8L)+2L)));
  return VALUES_1(foreign_pointer);
}
