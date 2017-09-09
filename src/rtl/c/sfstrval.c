/*
 * sfstrval.c -  Chestnut Run-Time Library entry for function set_foreign_string_value
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kcharacter;
extern Object Qarray_foreign_type;
extern Object Qpointer_foreign_type;
extern Object Qprimitive_foreign_type;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_string_base(Object o);
extern long ilength(Object sequence);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_string_base();
extern long ilength();

#endif



Object set_foreign_string_value(foreign_pointer,string)
    Object foreign_pointer,string;
{
  Object type,etype;
  char *dest = (char *)FOREIGN_POINTER_ADDRESS(foreign_pointer); //Delete "Declare_stack_pointer;" unreferenced local variable

  if(!(FOREIGN_POINTER_TYPE_P(foreign_pointer) &&
       POINTER_FOREIGN_TYPE_P(type = FOREIGN_POINTER_TYPE(foreign_pointer))))
    error(2,"~S is not a foreign-pointer of type :pointer",foreign_pointer);
  type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
  if(PRIMITIVE_FOREIGN_TYPE_P(type) &&
     Kcharacter == FOREIGN_TYPE_NAME(type))
    {
      int source_nchars = (int)ilength(string);
      MEMCPY(dest,SI_string_base(string),source_nchars);
      dest[source_nchars]='\0';      
    }
  else if(ARRAY_FOREIGN_TYPE_P(type) &&
	  PRIMITIVE_FOREIGN_TYPE_P(etype = ARRAY_FOREIGN_TYPE_ETYPE(type)) &&
	  Kcharacter == FOREIGN_TYPE_NAME(etype))
    {
      int source_nchars = (int)ilength(string);
      int dest_nchars = FOREIGN_TYPE_SIZE(type);
      int n;
      n = MIN(source_nchars,dest_nchars);
      MEMCPY(dest,SI_string_base(string),n);
      for(;n<dest_nchars;n++)
	dest[n]='\0';
    }
  else
    error(1,"set_foreign_string_value: not a pointer to character or array");
  return string;
}


