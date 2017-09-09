/*
 * unquetag.c -  Chestnut Run-Time Library entry for function UNIQUE_TAG
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"



/* This definition uses characters with a non-zero bits field
 * as tags, since these objects are seldom used.  
 */          

#define MIN_UNIQUE_TAG 0x100

#define MAX_UNIQUE_TAG (unsigned long)ICHAR_INT(-1L)

static unsigned int counter = MIN_UNIQUE_TAG;

Object UNIQUE_TAG()
{
  Object tag = CHR(counter);

  if ( counter == MAX_UNIQUE_TAG )
    counter = MIN_UNIQUE_TAG;
  else
    counter++;
  return tag;

  /* Was: */
  /*** Suboptimal.  We could use immediates, at least until we ran out. ***/
  /* return cons(FIX(0), NIL); */
}

