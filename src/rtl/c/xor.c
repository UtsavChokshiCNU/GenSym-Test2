/*
 * xor.c -  Chestnut Run-Time Library entry for function xor
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"
/* LUCID Extensions to Common Lisp */

Object xor(args)
  Object args;
{
    Declare_local_temp;
  long value = FALSE;

  for ( ; TRUEP(args); args = M_CDR(args))
    if (TRUEP(M_CAR(args))) value = !value;

  return VALUES_1(value ? T : NIL);
}
