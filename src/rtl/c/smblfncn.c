/*
 * smblfncn.c -  Chestnut Run-Time Library entry for function symbol_function
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern void SI_undefined_function_error(Object name);

#else

extern Object SI_symbol_field();
extern void SI_undefined_function_error();

#endif




/* symbol-function, setf of symbol-function, fboundp, fmakunbound */

Object symbol_function(symbol)
  Object symbol;
{
    Declare_local_temp;
  Object func;

  func = SI_symbol_field(symbol, SI_SymFn);
  if (func == UNBOUND) {
    SI_undefined_function_error(symbol);
    /*NOTREACHED*/
  }
  return VALUES_1(func);
}
