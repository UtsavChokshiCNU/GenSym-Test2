/*
 * spgvbnng.c -  Chestnut Run-Time Library entry for function SI_progv_do_bindings
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif



extern Object SI_set_symbol_value_helper();

void SI_progv_do_bindings(vals)
  Object vals;
{ Declare_protect(1);
  Stack_item *sp = Stack;
  Object sym, newval, temp = STACK_REF(-1);
  long count;

  PROTECT_LOCALS();
  PROTECT_1(vals);

  if (!FIXNUMP(temp)) {
    error(1, "progv_do_bindings: stack seems to be corrupt.");
    /*NOTREACHED*/
  }
  count = IFIX(temp);
  sp -= (2 * count) + 1;
  for ( ; count > 0; count--, sp += 2) {
    sym = sp->object;
    if (!SYMBOLP(sym)) {
      error(1, "progv_do_bindings: stack seems to be corrupt.");
      /*NOTREACHED*/
    }
    else if (!CONSP(vals)) newval = UNBOUND;
    else { newval = M_CAR(vals); vals = M_CDR(vals); }
    (void)SI_set_symbol_value_helper(sym, newval);
  }
  UNPROTECT_LOCALS();
}
