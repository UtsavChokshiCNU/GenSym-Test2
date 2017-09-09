/* $Revision: 10268 $ $Date: 2009-08-06 14:54:56 -0700 (Thu, 06 Aug 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Freescale StarCore
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define EINTR (-1)
#define ENOSYS (-2)
#define PATH_MAX 128
#define S_IRUSR 0x0100
#define S_IWUSR 0x0080
#define _ABI_2_0
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "cmn-autoSave.h"
#include "covrt.c"
