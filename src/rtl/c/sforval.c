/*
 * sforval.c -  Chestnut Run-Time Library entry for function set_foreign_value
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



Object set_foreign_value(foreign_pointer,value)
    Object foreign_pointer,value;
{
  Object type;

  if(!(FOREIGN_POINTER_TYPE_P(foreign_pointer) && 
       POINTER_FOREIGN_TYPE_P(type = FOREIGN_POINTER_TYPE(foreign_pointer))))
    error(2,"~S is not a foreign-pointer of type (:pointer *)",
	  foreign_pointer);
  type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
  return 
    (*FOREIGN_TYPE_WRITER(type))
      (type,(char *)FOREIGN_POINTER_ADDRESS(foreign_pointer),value);
}
