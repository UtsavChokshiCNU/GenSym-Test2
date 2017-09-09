/*
 * gc.c - Automatic memory management globals, handlers and intializer 
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"

extern Object Gc_inhibit;
extern Object Gc_silence;

extern void (*SI_garbage_collect_fptr)();
extern void SI_garbage_collect();
extern long SI_gc_silence_init;

/* Must be called on startup in order to setup GC 
   without a call, the GC is never linked in */

SI_INIT_automatic_gc ()
{
  SI_garbage_collect_fptr  = SI_garbage_collect;
  if (Gc_inhibit == SI_UNINITIALIZED_MARKER)
    Gc_inhibit = NIL;
  if (Gc_silence == SI_UNINITIALIZED_MARKER)
    Gc_silence = SI_gc_silence_init ? T : NIL;
}

