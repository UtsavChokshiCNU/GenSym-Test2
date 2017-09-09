/*
 * boundp.c -  Chestnut Run-Time Library entry for function boundp
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);

#else

extern Object SI_symbol_field();

#endif



Object boundp(symbol)
  Object symbol;
{
    Declare_local_temp;
  if (SELF_EVALUATING_SYMBOL_P(symbol))
    return VALUES_1(T);
  else
    return VALUES_1(SI_symbol_field(symbol, SI_SymBnd));
}
