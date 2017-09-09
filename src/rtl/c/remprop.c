/*
 * remprop.c -  Chestnut Run-Time Library entry for function remprop
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);
extern Object do_remf(Object,Object);

#else

extern Object SI_set_symbol_field();
extern Object SI_symbol_field();
extern Object do_remf();

#endif




Object remprop(symbol, indicator)
  Object symbol, indicator;
{
    Declare_local_temp;
  Object	plist = do_remf(SYMBOL_PLIST(symbol), indicator);

  if (plist == T) return VALUES_1(NIL);
  else { SET_SYMBOL_PLIST(symbol, plist); return VALUES_1(plist); }
}
