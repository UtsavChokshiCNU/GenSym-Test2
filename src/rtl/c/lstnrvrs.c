/*
 * lstnrvrs.c -  Chestnut Run-Time Library entry for function list_nreverse
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object nreverse(Object);

#else

extern Object nreverse();

#endif


/* LUCID Extensions to Common Lisp */

Object list_nreverse(lst)
  Object lst;
{ return nreverse(lst); }
