/*
 * cnsnlndl.c -  Chestnut Run-Time Library entry for function constantly_handler
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qconstantly_false;
extern Object Qconstantly_true;
extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern Object MAKE_FUNCTION(Object (*entry)(), Object env, long variadicp, long nreq, long npos);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);

#else

extern Object MAKE_FUNCTION();
extern Object SI_symbol_field();

#endif

#define Fconstantly_false SYMBOL_FUNCTION(Qconstantly_false)
#define Fconstantly_true SYMBOL_FUNCTION(Qconstantly_true)


/*ARGSUSED*/
static Object constantly_handler varargs_1(int, n)
{
    Declare_local_temp;
  return VALUES_1(SI_FUNCTION_ENV(SI_Called_function)); 
}

Object constantly(value)
  Object value;
{
    Declare_local_temp;
  Object function;

  if (value == NIL) function = Fconstantly_false;
  else if (value == T) function = Fconstantly_true;
  else function = MAKE_FUNCTION(constantly_handler, value, TRUE, 0, 0);
  return VALUES_1(function);
}
