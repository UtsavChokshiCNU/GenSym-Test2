/* $Revision: 10765 $ $Date: 2010-01-14 15:12:45 -0800 (Thu, 14 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for POSIX
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#if __APPLE__
	#define _POSIX_C_SOURCE 199506L
#endif
#if __sun
	#define _POSIX_C_SOURCE 199506L
#endif

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#if !Libcov_noAutoSave
	#include <pthread.h>

	/* Override pthread_join to disable it.
	 * 1. It is unnecessary for us on POSIX; threads end upon process termination
	 * 2. It is broken in uclibc, symptom: it never returns
	 */
	#define pthread_join Libcov_pthread_join
	static int Libcov_pthread_join(pthread_t thread, void** value_ptr)
	{
		thread = thread;
		value_ptr = value_ptr;
		return 0;
	}
#endif
#include "cmn-getenvFile.h"

#if __linux
	/* Shared pthread library might not be initialized early enough */
	#define isReady() (__errno_location() != NULL)
#endif

/* getenv */
static char* Libcov_getenv(const char* name)
{
	char* value = getenv(name);
	if (value == NULL) {
		value = getenvFile(name, "/tmp/BullseyeCoverageEnv.txt");
	}
	if (value == NULL) {
		value = getenvFile(name, "/etc/BullseyeCoverageEnv.txt");
	}
	return value;
}
#define getenv Libcov_getenv

#define Libcov_interface 3
#define Libcov_posix 1
#include "atomic.h"
#include "libcov.h"
#include "cmn-autoSave.h"
#include "covrt.c"
