/* $Revision: 10699 $ $Date: 2009-12-22 14:58:17 -0800 (Tue, 22 Dec 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for TI Code Composer
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define PATH_MAX 128
#define S_IRUSR 0
#define S_IWUSR 0
#define EINTR (-1)
#define ENOSYS (-2)
#include <errno.h>
#include <file.h>
#include <limits.h>
#include <stdlib.h>
#if _TMS320C3x || _TMS320C4x
	#include <stdio.h>
	typedef long off_t;
#endif

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
#include "covrt.c"
