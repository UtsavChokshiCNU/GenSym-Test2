#ifdef _GENSYM_GDB_DEBUG_

#  include "kernel.h"
#  include "uconfig.h"

Object isvref_function (place, index)
  Object place;
  long index;
{
  return ISVREF(place, index);
}

long ifix_function (fixnum_obj)
  Object fixnum_obj;
{
  return IFIX(fixnum_obj);
}

Object fix_function (integer)
  long integer;
{
  return FIX(integer);
}


#endif /* _GENSYM_GDB_DEBUG_ */

