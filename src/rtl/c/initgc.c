/*
 * initgc.c - non-garbage-collecting handler for "not enough memory"
 *            events
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();
extern Object (*SI_warn_fptr) ();

#endif



#if SI_COPYING_COLLECTOR
CONFIG_PROVIDES(SI_config_copying_collector)
#else
CONFIG_PROVIDES(SI_config_not_copying_collector)
#endif

void SI_no_gc()
{
    warn(1, "Memory exhausted. GC is not allowed. ");
    error(1,"Please change the configuration to allow more memory or GC");
}

void (*SI_garbage_collect_fptr)() = SI_no_gc;

void SI_initgc_ENSURE() {}
