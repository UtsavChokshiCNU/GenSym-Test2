/* $Revision: 10871 $ $Date: 2010-02-19 11:47:44 -0800 (Fri, 19 Feb 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Analog Devices VisualDSP++
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define EINTR (-1)
#define PATH_MAX 128
typedef long off_t;
#include "cmn-stdio.h"

#include "cmn-getenvFile.h"
static char* Libcov_getenv(const char* name)
{
	char* value = getenv(name);
	if (value == NULL) {
		value = getenvFile(name, "/BullseyeCoverageEnv.txt");
	}
	return value;
}
#define getenv Libcov_getenv

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
