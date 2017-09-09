/*
 * smvfncll.c -  Chestnut Run-Time Library entry for function SI_mv_funcall
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object SI_internal_funcall(Object original_function, long args_on_stack, Object arglist);

#else

extern Object (*SI_error_fptr) ();
extern Object SI_internal_funcall();

#endif



Object SI_mv_funcall(fn)
  Object	fn;
{ Object	count;

  count = STACK_POP();
  if (!FIXNUMP(count)) {
    error(1, "MV_FUNCALL: stack seems to be corrupt.");
    /*NOTREACHED*/
  }
  else return SI_internal_funcall(fn, IFIX(count), NIL);
  return NULL; //this function return somthing
}
