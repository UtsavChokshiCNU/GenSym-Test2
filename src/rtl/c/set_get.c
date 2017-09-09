/*
 * set_get.c -  Chestnut Run-Time Library entry for function set_get
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qsymbol;

#if SI_USE_PROTOTYPES

extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern void SI_type_error(Object datum, Object expected_type);
extern Object set_getf(Object,Object,Object);

#else

extern Object SI_set_symbol_field();
extern Object SI_symbol_field();
extern void SI_type_error();
extern Object set_getf();

#endif





Object set_get(sym, key, value)
  Object sym, key, value;
{
    Declare_local_temp;
  Declare_protect(2);
  Object plist;

  PROTECT_LOCALS();
  PROTECT_2(sym, value);

  if (!SYMBOLP(sym)) { SI_type_error(sym, Qsymbol); /*NOTREACHED*/ }
  plist = set_getf(SYMBOL_PLIST(sym), key, value);
  SET_SYMBOL_PLIST(sym, plist);
  UNPROTECT_LOCALS();
  return VALUES_1(value);
}
