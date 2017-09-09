// $Revision: 10767 $ $Date: 2010-01-20 14:15:27 -0800 (Wed, 20 Jan 2010) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
//
// BullseyeCoverage run-time definitions for VxWorks

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define Libcov_covfile "/tgtsvr/test.cov"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <version.h>

// atexit on VxWorks 6.6 DLKM returns -1 errno=0
static int Libcov_atexit(void (*function)(void))
{
	const int status = atexit(function);
	if (status != 0) {
		errno = ENOSYS;
	}
	return status;
}
#define atexit Libcov_atexit

// fcntl on VxWorks 6.6 RTP returns -1 errno=ENOTSUP
#include "stub-fcntl.h"

#if _WRS_VXWORKS_MAJOR * 100 + _WRS_VXWORKS_MINOR <= 602
	#include "stub-nanosleep.h"
	#include "stub-pthread.h"
#endif

#define Libcov_interface 3
#define Libcov_posix 1
#include "atomic.h"
#include "libcov.h"
#include "cmn-autoSave.h"
#include "covrt.c"
