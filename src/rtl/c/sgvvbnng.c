/*
 * sgvvbnng.c -  Chestnut Run-Time Library entry for function SI_progv_save_bindings
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_symbol_field(Object sym, enum SI_Symbol_field field);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_symbol_field();

#endif



void SI_progv_save_bindings(syms)
  Object syms;
{ Object sym, oldval;
  int count = 0;

  while (syms != NIL) {
    sym = M_CAR(syms);
    if (SELF_EVALUATING_SYMBOL_P(sym)) {
      error(2, "PROGV: Invalid variable ~S.", sym);
      /*NOTREACHED*/
    }
    syms = M_CDR(syms);
    oldval = SI_symbol_field(sym, SI_SymVal);
    STACK_PUSH(sym);
    STACK_PUSH(oldval);
    count++;
  }
  STACK_PUSH(FIX(count));
}
