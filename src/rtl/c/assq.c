/*
 * assq.c -  Chestnut Run-Time Library entry for function assq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object assoc_eq(Object key, Object alist);

#else

extern Object assoc_eq();

#endif


/* LUCID Extensions to Common Lisp */

Object assq(key, alist)
  Object key;
  Object alist;
{ return assoc_eq(key, alist); }
