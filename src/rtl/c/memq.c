/*
 * memq.c -  Chestnut Run-Time Library entry for function memq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object member_eq(Object item, Object list);

#else

extern Object member_eq();

#endif


/* LUCID Extensions to Common Lisp */

Object memq(key, list)
  Object key;
  Object list;
{ return member_eq(key, list); }
