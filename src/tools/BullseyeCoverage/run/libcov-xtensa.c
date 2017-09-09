/* $Revision: 10375 $ $Date: 2009-09-09 16:58:46 -0700 (Wed, 09 Sep 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Tensilica Xtensa.
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define PATH_MAX 128
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int Libcov_open(const char* path, int oflag, int mode)
{
	return open(path, oflag | O_BINARY, mode);
}
#define open Libcov_open

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "cmn-getenvFile.h"

static char* Libcov_getenv(const char* name)
{
	return getenvFile(name, "/BullseyeCoverageEnv.txt");
}
#define getenv Libcov_getenv

#include "covrt.c"
