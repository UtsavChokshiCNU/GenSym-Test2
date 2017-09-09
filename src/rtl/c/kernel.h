/*
   Include file for C code produced by V3+ translator
 */

#ifndef SI_KERNEL_DOT_H

#define SI_KERNEL_DOT_H

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <ctype.h>
#include <math.h>

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN // This prevents interface to be defined as struct in objbase.h
							// via ole2.h
#include <windows.h>
#endif

#include "longname.h"

#include "config.h"
#include "object.h"
#include "values.h"
#include "svarargs.h"
#include "core.h"
#include "instance.h"
#include "inline.h"
#include "specific.h"
#include "ffi.h"

#if SI_SUPPORT_CLOS
#include "clos.h"
#endif

#if SI_SUPPORT_THREAD
#include <pthread.h>
#include <sched.h>
#endif

#include "thread.h"
#include "lock.h"
#include "special.h"
#include "atomic.h"

#include "smcompat.h"

#include "externs.h"

#ifndef SKIP_SI_VARIADIC_KEYWORD_FUNCTIONS
#define SI_VARIADIC_KEYWORD_FUNCTIONS
#endif

#include "varkey.h"

/* Include Gensym's additional macros.  -jra 9/20/93
 */

#ifndef CHESTNUT
#include "gensym.h"
#endif

#endif /* SI_KERNEL_DOT_H */




