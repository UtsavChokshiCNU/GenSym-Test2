/*
 * ssvmrvls.c -  Chestnut Run-Time Library entry for function SI_save_more_values
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];

#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif



void SI_save_more_values(result)
  Object result;
{ Object	count;
  long		i, j;

  count = STACK_REF(-1);
  if (!FIXNUMP(count)) {
    error(1, "SAVE_MORE_VALUES: stack seems to be corrupt.");
    /*NOTREACHED*/
  }
  else if (Values_count > 0) {
    Stack += Values_count;
    j = -1L - Values_count;
    STACK_REF(j++) = result;
    for (i = 0; j < -1L; )
      STACK_REF(j++) = Values[i++];
    STACK_REF(-1L) = FIXNUM_ADD(count, FIX(Values_count));
  }
  /* else don't need to do anything. */
}
