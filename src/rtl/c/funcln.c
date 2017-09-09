/*
 * funcln.c - internal funcall routines
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

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

/* funcall[0-2] : for non-variadic calls only when SI_SUPPORT_CLOS === 0     */
/* These three functions are no longer defined when SI_SUPPORT_CLOS is true, */
/* see object.h */

#if SI_SUPPORT_CLOS
#else

Object funcall0 (func)
    Object func;
{
    Object funcallable, env;
    Object (*entry)();
    
    RESOLVE_FUNCALLABLE_OBJECT(func, funcallable);
    entry = SI_FUNCTION_ENTRY(funcallable);
    if(FIXNUMP(env = SI_FUNCTION_ENV(funcallable))) {
      Object value;
      
      if(SI_FUNCTION_VARIADIC_P(funcallable))
	value = (*entry)(0);
      else if(SI_FUNCTION_SIMPLE_P(funcallable))
	value = (*entry)();
      else if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	value = (*entry)(SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
      else
	value = (*entry)(SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
      Values_count = IFIX(env);
      return value;
    }
    if(SI_FUNCTION_VARIADIC_P(funcallable))
      return (*entry)(0);
    if(SI_FUNCTION_SIMPLE_P(funcallable))
      return (*entry)();
    if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
      return (*entry)(SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
    return (*entry)(SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
}


Object funcall1 (func, arg)
    Object func, arg;
{
    Object funcallable, env;
    Object (*entry)();
    
    RESOLVE_FUNCALLABLE_OBJECT(func, funcallable);
    entry = SI_FUNCTION_ENTRY(funcallable);
    if(FIXNUMP(env = SI_FUNCTION_ENV(funcallable))) {
      Object value;
      
      if(SI_FUNCTION_VARIADIC_P(funcallable))
	value = (*entry)(1, arg);
      else if(SI_FUNCTION_SIMPLE_P(funcallable))
	value = (*entry)(arg);
      else if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	value = (*entry)(arg,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
      else
	value = (*entry)(arg,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
      Values_count = IFIX(env);
      return value;
    }
    if(SI_FUNCTION_VARIADIC_P(funcallable))
      return (*entry)(1, arg);
    if(SI_FUNCTION_SIMPLE_P(funcallable))
      return (*entry)(arg);
    if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
      return (*entry)(arg,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
    return (*entry)(arg,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
}

Object funcall2 (func, arg1, arg2)
    Object func, arg1, arg2;
{
    Object funcallable, env;
    Object (*entry)();

    RESOLVE_FUNCALLABLE_OBJECT(func, funcallable);
    entry = SI_FUNCTION_ENTRY(funcallable);
    if(FIXNUMP(env = SI_FUNCTION_ENV(funcallable))) {
      Object value;

      if(SI_FUNCTION_VARIADIC_P(funcallable))
	value = (*entry)(2, arg1, arg2);
      else if(SI_FUNCTION_SIMPLE_P(funcallable))
	value = (*entry)(arg1, arg2);
      else if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	value = (*entry)(arg1,arg2,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
      else
	value = (*entry)(arg1,arg2,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
      Values_count = IFIX(env);
      return value;
    }
    if(SI_FUNCTION_VARIADIC_P(funcallable))
      return (*entry)(2, arg1, arg2);
    if(SI_FUNCTION_SIMPLE_P(funcallable))
      return (*entry)(arg1, arg2);
    if(SI_NEEDS_FEW_UNSUPPLIED(funcallable))
	return (*entry)(arg1,arg2,SI_SUPPLY_UNSUPPLIED_ARGUMENTS());
    return (*entry)(arg1,arg2,SI_SUPPLY_MORE_UNSUPPLIED_ARGUMENTS());
}

#endif

void SI_bad_funcallable_error(function, original_function)
    Object function, original_function;
{
    if (function == UNBOUND) {
	SI_undefined_function_error(original_function);
	/*NOTREACHED*/
    }
    else {
	SI_type_error(function, Qfunction);
	/*NOTREACHED*/
    }
}
