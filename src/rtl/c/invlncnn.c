/*
 * invlncnn.c -  Chestnut Run-Time Library entry for function invalid_function_name_error
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qsetf;

#if SI_USE_PROTOTYPES

extern Object STATIC_STRING(char *s);
extern Object (*SI_errorn_fptr) (int,...);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object set_setf_function(Object,Object);
extern Object set_symbol_function(Object,Object);
extern Object setf_function(Object);
extern Object symbol_function(Object);

#else

extern Object STATIC_STRING();
extern Object (*SI_errorn_fptr) ();
extern Object SI_set_symbol_field();
extern Object SI_symbol_field();
extern Object set_setf_function();
extern Object set_symbol_function();
extern Object setf_function();
extern Object symbol_function();

#endif



#undef VALIDATE_SETF_FUNCTION_NAME
#ifdef DEBUG

#define VALIDATE_SETF_FUNCTION_NAME(name) \
    if (!(CONSP(name) && \
	  CONSP(M_CDR(name)) && \
	  (M_CDR(M_CDR(name)) == NIL) && \
	  (M_CAR(name) == Qsetf) && \
	  SYMBOLP(M_CAR(M_CDR(name))))) \
      invalid_function_name_error(name)

static void invalid_function_name_error(name)
  Object name;
{ SI_Declare_static_string(estr, d, "Invalid function name: ~S.");

  (void)errorn(2, estr, name);
  /*NOTREACHED*/
}

#else /* #elif !defined(DEBUG) */

#define VALIDATE_SETF_FUNCTION_NAME(name)	/* Nothing */

#endif /* defined(DEBUG) */

#define SETF_FUNCTION_NAME_SYMBOL(name)	M_CADR(name)

Object fdefinition(name)
  Object name;
{
    Declare_local_temp;
  if (SYMBOLP(name)) return symbol_function(name);
  VALIDATE_SETF_FUNCTION_NAME(name);
  return setf_function(SETF_FUNCTION_NAME_SYMBOL(name));
}
    
Object set_fdefinition(name, value)
  Object name, value;
{
    Declare_local_temp;
  if (SYMBOLP(name)) return set_symbol_function(name, value);
  VALIDATE_SETF_FUNCTION_NAME(name);
  return set_setf_function(SETF_FUNCTION_NAME_SYMBOL(name), value);
}

Object fboundp(name)
  Object name;
{
    Declare_local_temp;
  Object res;

  if (SYMBOLP(name))
    res = SI_symbol_field(name, SI_SymFbnd);
  else {
    VALIDATE_SETF_FUNCTION_NAME(name);
    res = SI_symbol_field(SETF_FUNCTION_NAME_SYMBOL(name), SI_SymSetfFbnd);
  }
  return VALUES_1(res);
}  

Object fmakunbound(name)
  Object name;
{
    Declare_local_temp;
  Declare_protect(1);

  PROTECT_LOCALS();
  PROTECT_1(name);

  if (SYMBOLP(name))
    SI_set_symbol_field(name, UNBOUND, SI_SymFbnd);
  else {
    VALIDATE_SETF_FUNCTION_NAME(name);
    SI_set_symbol_field(SETF_FUNCTION_NAME_SYMBOL(name),
			UNBOUND,
			SI_SymSetfFbnd);
  }
  UNPROTECT_LOCALS();
  return VALUES_1(name);
}
#undef VALIDATE_SETF_FUNCTION_NAME
#undef INIT_SETF_FUNCTION_TABLE

