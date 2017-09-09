/*
 * cmplmnnl.c -  Chestnut Run-Time Library entry for function complement_handler
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern Object MAKE_FUNCTION(Object (*entry)(), Object env, long variadicp, long nreq, long npos);
extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);

#else

extern Object MAKE_FUNCTION();
extern Object SI_internal_funcall();

#endif




static Object complement_handler varargs_1(int, n)
{
    Declare_local_temp;
  va_list ap;
  long i;
  Object function = SI_Called_function;
  Object value;

  SI_va_start(ap,n);
  for (i = 0; i < n; i++) STACK_PUSH(va_arg(ap, Object));
  va_end(ap);

  function = SI_FUNCTION_ENV(function);
  value = SI_internal_funcall(function, n, NIL);
  return VALUES_1(TRUEP(value) ? NIL : T);
}

Object complement(function)
  Object function;
{
    Declare_local_temp;
  Object value;

  value = MAKE_FUNCTION(complement_handler, function, TRUE, 0, 0);
  return VALUES_1(value);
}
