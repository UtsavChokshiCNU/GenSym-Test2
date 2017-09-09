/* $Revision: 9609 $ $Date: 2009-01-08 17:31:04 -0800 (Thu, 08 Jan 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Green Hills Software INTEGRITY
 * http://www.ghs.com
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define Error ghs_Error
#include <errno.h>
#include <fcntl.h>
#include <ind_io.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#undef Error
#define PATH_MAX _POSIX_PATH_MAX

// fcntl
static int Libcov_fcntl(int fildes, int cmd, struct flock* arg)
{
	const int status = fcntl(fildes, cmd, arg);
	// If failure with invalid errno
	if (status == -1 && errno == ENOENT) {
		// Set errno indicating fcntl is not available
		errno = ENOSYS;
	}
	return status;
}
#define fcntl Libcov_fcntl

// open
//   First try host i/o and then if that fails try native i/o
static int Libcov_open(const char* path, int oflag, int mode)
{
	int fd = hostio_open(path, oflag);
	if (fd == -1) {
		fd = open(path, oflag, mode);
	}
	return fd;
}
#define open Libcov_open

// getenv
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
#include "cmn-autoSave.h"
#include "covrt.c"
