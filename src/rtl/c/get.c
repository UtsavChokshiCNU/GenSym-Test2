/*
 * get.c -  Chestnut Run-Time Library entry for function get
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Qsymbol;

#if SI_USE_PROTOTYPES

extern void SI_type_error(Object datum, Object expected_type);

#else

extern void SI_type_error();

#endif

extern Object SI_Plist_of_nil;




Object get (sym, key, def)
  Object sym, key, def;
{
  Object plist, next_cdr;
  if (!SYMBOLP(sym)) { SI_type_error(sym, Qsymbol); /*NOTREACHED*/ };
  plist = ((sym) == NIL ? SI_Plist_of_nil : SI_SYMBOL_PLIST(sym));
  while(TRUEP(plist)) {
    next_cdr = M_CDR(plist);
    if (key == M_CAR(plist)) {
      return VALUES_1(M_CAR(next_cdr));
    }
    plist = M_CDR(next_cdr);
  }
  return VALUES_1(SUPPLIED_P(def) ? def : NIL);
}
