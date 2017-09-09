/*
 * ccl.c -  Chestnut Run-Time Library entry for function constant_initfunction_handler
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qconstantly_nil_initfunction;
extern Object Qconstantly_t_initfunction;
extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object gethash(Object,Object,Object);
extern Object make_hash_table(Object test, Object size, Object rehash_size, Object rehash_threshold);
extern Object set_gethash(Object,Object,Object);

#else

extern void SI_add_external_root();
extern Object SI_symbol_field();
extern Object STATIC_FUNCTION1();
extern Object gethash();
extern Object make_hash_table();
extern Object set_gethash();

#endif

#define Fconstantly_nil_initfunction SYMBOL_FUNCTION(Qconstantly_nil_initfunction)
#define Fconstantly_t_initfunction SYMBOL_FUNCTION(Qconstantly_t_initfunction)

static Object Constant_initfunctions = UNBOUND;

static Object constant_initfunction_handler()
{
    Declare_local_temp;
  return VALUES_1(SI_FUNCTION_ENV(SI_Called_function)); 
}

Object constant_initfunction(value)
  Object value;
{
    Declare_local_temp;
  Declare_protect(1);
  Object function;

  PROTECT_LOCALS();
  PROTECT_1(value);

  if (value == NIL) function = Fconstantly_nil_initfunction;
  else if (value == T) function = Fconstantly_t_initfunction;
  else {
    if (Constant_initfunctions == UNBOUND) {
      PROTECT_GLOBAL(Constant_initfunctions);
      Constant_initfunctions = make_hash_table(KOPT, KOPT, KOPT, KOPT);
    }
    function = gethash(value, Constant_initfunctions, NIL);
    if (!TRUEP(function)) {
      function =
	STATIC_FUNCTION(constant_initfunction_handler, value, FALSE, 0, 0);
      function = set_gethash(value, Constant_initfunctions, function);
    }
  }
  UNPROTECT_LOCALS();
  return VALUES_1(function);
}
