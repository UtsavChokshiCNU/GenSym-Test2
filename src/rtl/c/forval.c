/*
 * forval.c -  Chestnut Run-Time Library entry for function foreign_value
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qpointer_foreign_type;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif



Object foreign_value(foreign_pointer)
    Object foreign_pointer;
{
  Object type;

  if(!(FOREIGN_POINTER_TYPE_P(foreign_pointer) && 
       POINTER_FOREIGN_TYPE_P(type = FOREIGN_POINTER_TYPE(foreign_pointer))))
    error(2,"~S is not a foreign-pointer of type (:pointer *)",
	  foreign_pointer);
  type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
  return 
    (*FOREIGN_TYPE_READER(type))
      (type,(char *)FOREIGN_POINTER_ADDRESS(foreign_pointer));
}
