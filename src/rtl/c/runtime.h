/*
 * runtime.h - LISP-TO-C runtime system structures and defines
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 * This file is not #included by translated user files.
 */
#ifndef RUNTIME_H
#define RUNTIME_H

#define SI_RUNTIME_INTERNAL

#ifndef SI_KERNEL_DOT_H

#include <stdio.h>
#include <setjmp.h>
#include <ctype.h>
#include <assert.h>

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
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#endif

#include "thread.h"
#include "lock.h"
#include "special.h"
#include "atomic.h"

#endif

/* should use something like SI_SMCOMPAT here */
#ifdef SI_VARIADIC_KEYWORD_FUNCTIONS
#include "smcompat.h"
#endif

#include "varkey.h"
 
#include "runint.h"

#ifndef CHESTNUT
#define CHESTNUT  /* for bignum.h */
#endif

#include "bignum.h"

#endif /* RUNTIME_H */
