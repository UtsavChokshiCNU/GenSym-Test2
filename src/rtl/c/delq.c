/*
 * delq.c -  Chestnut Run-Time Library entry for function delq
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object delete_eq(Object item, Object list);

#else

extern Object delete_eq();

#endif


/* LUCID Extensions to Common Lisp */

Object delq(item, lst)
  Object item;
  Object lst;
{ return delete_eq(item, lst); }
