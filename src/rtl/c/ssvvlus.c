/*
 * ssvvlus.c -  Chestnut Run-Time Library entry for function SI_save_values
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern TLS Object Values[];


/* First argument, if present, is already on the stack. */
void SI_save_values ()
{ long i, j;

  Stack += Values_count;
  for (i = 0, j = -Values_count; j < -1L; )
    STACK_REF(j++) = Values[i++];
  STACK_REF(-1L) = FIX(Values_count);
}
