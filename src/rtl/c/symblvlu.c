/*
 * symblvlu.c -  Chestnut Run-Time Library entry for function symbol_value
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern void SI_unbound_variable_error(Object name);

#else

extern Object SI_symbol_field();
extern void SI_unbound_variable_error();

#endif



Object symbol_value(symbol)
  Object symbol;
{
  Declare_local_temp;
  Object value;

  if (SELF_EVALUATING_SYMBOL_P(symbol))
    return VALUES_1(symbol);
  value = SI_symbol_field(symbol, SI_SymVal);
  if (value == UNBOUND) {
    SI_unbound_variable_error(symbol);
    /*NOTREACHED*/
  }
  return VALUES_1(value);
}
