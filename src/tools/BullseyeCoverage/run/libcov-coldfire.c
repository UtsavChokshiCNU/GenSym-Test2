/* $Revision: 10383 $ $Date: 2009-09-11 18:08:19 -0700 (Fri, 11 Sep 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Freescale CodeWarrior for ColdFire
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define _MSL_OS_DISK_FILE_SUPPORT 1
#define PATH_MAX 128
#define getcwd __msl_getcwd
#include <errno.h>
#include <stdlib.h>
typedef long off_t;
#include "cmn-stdio.h"
#include "stub-fcntl.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"

/*---------------------------------------------------------------------------
// BullseyeCoverage run-time code
*/
#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "cmn-autoSave.h"
#include "covrt.c"
