/* $Revision: 10536 $ $Date: 2009-10-27 14:39:47 -0700 (Tue, 27 Oct 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for IAR Systems simulator
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <errno.h>
#include <stdlib.h>
#include <yfuns.h>

#define EINTR (-1)
#define ENOSYS (-2)
#define PATH_MAX 512
#define O_CREAT _LLIO_CREAT
#define O_RDONLY _LLIO_RDONLY
#define O_WRONLY _LLIO_WRONLY
#define O_RDWR _LLIO_RDWR
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
typedef long off_t;

#define open(path, oflag, mode) __open(path, oflag | _LLIO_BINARY)
#define close __close
#define read(fildes, buf, nbyte) __read(fildes, (unsigned char*)(buf), nbyte)
#define write(filedes, buf, nbyte) __write_buffered(filedes, (const unsigned char*)(buf), nbyte)
#define lseek __lseek

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
