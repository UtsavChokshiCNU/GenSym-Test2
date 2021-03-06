/*
 * ssffncn.c -  Chestnut Run-Time Library entry for function set_setf_function
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);

#else

extern Object SI_set_symbol_field();

#endif




Object set_setf_function(symbol, value)
  Object symbol, value;
{
    Declare_local_temp;
  return VALUES_1(SI_set_symbol_field(symbol, value, SI_SymSetfFn)); 
}
