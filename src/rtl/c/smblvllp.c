/*
 * smblvllp.c -  Chestnut Run-Time Library entry for function SI_set_symbol_value_helper
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_set_symbol_field();

#endif



Object SI_set_symbol_value_helper(symbol, value)
  Object symbol, value;
{ if (SELF_EVALUATING_SYMBOL_P(symbol)) {
    (void)error(3, "Attempting to set value of ~S to ~S.", symbol, value);
    /*NOTREACHED*/
  }
  else
    return SI_set_symbol_field(symbol, value, SI_SymVal);
  return NULL; //this function return somthing
}
