/*******************************************************************************

File name:               gensym-features.h
Owner:                   Peter Fandel

Purpose:                 This include file serves to define and include those
                         features required to support various platforms.

This file depends on:    Nothing.

Dependent files:         ??

History:                 15oct92  PAF  Cleaned out & Rewritten.


*******************************************************************************/

#include <stdio.h>
#include <string.h>

#ifndef NULL
#  define NULL 0L
#endif

#include <signal.h>  /* for gsi_watchdog() */

#include <time.h>
#ifdef unix
#  include <sys/time.h>
#endif

#if !defined(sun)
#  include <stdlib.h>
#endif

#ifndef __APPLE__
#  include <malloc.h>
#endif
