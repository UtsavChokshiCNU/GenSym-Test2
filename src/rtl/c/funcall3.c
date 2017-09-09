/*
 * funcall3.c -  Chestnut Run-Time Library entry for function funcall3
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_SUPPORT_CLOS

#if SI_USE_PROTOTYPES

extern Object SI_internal_funcall(Object original_function, int args_on_stack, Object arglist);

#else

extern Object SI_internal_funcall();

#endif

Object funcall3 (func, arg1, arg2, arg3)
    Object func, arg1, arg2, arg3;
{
    Stack += 3;
    STACK_REF(-3) = arg1;
    STACK_REF(-2) = arg2;
    STACK_REF(-1) = arg3;
    return SI_internal_funcall(func, 3, NIL);
}

#else

extern Object Qfunction;
extern TLS Object SI_Called_function;

#if SI_USE_PROTOTYPES

extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern void SI_type_error(Object datum, Object expected_type);
extern void SI_undefined_function_error(Object name);

#else

extern Object SI_symbol_field();
extern void SI_type_error();
extern void SI_undefined_function_error();

#endif

#include "funcall.h"

Object funcall3 (func, arg1, arg2, arg3)
    Object func, arg1, arg2, arg3;
{
    Object funcallable, env;
    Object (*entry)();

    RESOLVE_FUNCALLABLE_OBJECT(func, funcallable);
    entry = SI_FUNCTION_ENTRY(funcallable);
    if(FIXNUMP(env = SI_FUNCTION_ENV(funcallable))) {
      Object value;

      if(SI_FUNCTION_VARIADIC_P(funcallable))
	value = (*entry)(2, arg1, arg2, arg3);
      else if(SI_FUNCTION_SIMPLE_P(funcallable))
	value = (*entry)(arg1, arg2, arg3);
      else if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	value = (*entry)(arg1,arg2,arg3,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
      else
	value = (*entry)(arg1,arg2,arg3,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
      Values_count = IFIX(env);
      return value;
    }
    if(SI_FUNCTION_VARIADIC_P(funcallable))
      return (*entry)(2, arg1, arg2, arg3);
    if(SI_FUNCTION_SIMPLE_P(funcallable))
      return (*entry)(arg1, arg2, arg3);
    if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	return (*entry)(arg1,arg2,arg3,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
    return (*entry)(arg1,arg2,arg3,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
}

#endif
