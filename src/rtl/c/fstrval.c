/*
 * fstrval.c -  Chestnut Run-Time Library entry for function foreign_string_value
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kcharacter;
extern Object Qarray_foreign_type;
extern Object Qbase_char;
extern Object Qpointer_foreign_type;
extern Object Qprimitive_foreign_type;

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_string_base(Object o);
extern Object istring_to_string_or_nil(char *istring);
extern Object make_array(Object dimensions, Object element_type, Object initial_element, Object initial_contents, Object adjustable, Object fill_pointer, Object displaced_to, Object displaced_index_offset);

#else

extern Object (*SI_error_fptr) ();
extern char *SI_string_base();
extern Object istring_to_string_or_nil();
extern Object make_array();

#endif



Object foreign_string_value(foreign_pointer)
    Object foreign_pointer;
{
  Object type,etype;
  char *address;
  Declare_stack_pointer;

  if(!(FOREIGN_POINTER_TYPE_P(foreign_pointer) &&
       POINTER_FOREIGN_TYPE_P(type = FOREIGN_POINTER_TYPE(foreign_pointer))))
    error(2,"~S is not a foreign-pointer of type :pointer",foreign_pointer);
  address = (char *)FOREIGN_POINTER_ADDRESS(foreign_pointer);
  type = POINTER_FOREIGN_TYPE_TO_TYPE(type);
  if(PRIMITIVE_FOREIGN_TYPE_P(type) &&
     Kcharacter == FOREIGN_TYPE_NAME(type))
    return istring_to_string_or_nil(address);
  else if(ARRAY_FOREIGN_TYPE_P(type) &&
	  PRIMITIVE_FOREIGN_TYPE_P(etype = ARRAY_FOREIGN_TYPE_ETYPE(type)) &&
	  Kcharacter == FOREIGN_TYPE_NAME(etype))
    {
      Object result = UNBOUND;
      char *resultstr;
      int len;

      SAVE_STACK();
      PROTECT_2(foreign_pointer,type);
      result = make_array(ARRAY_FOREIGN_TYPE_DIMENSIONS(type),Qbase_char,
			  _,_,_,_,_,_);
      len = FOREIGN_TYPE_SIZE(type);
      resultstr = SI_string_base(result);
      MEMCPY(resultstr,address, len);
      RESTORE_STACK();
      return VALUES_1(result);
    }
  else
    error(1,"foreign_string_value: not a pointer to character or array");
}



