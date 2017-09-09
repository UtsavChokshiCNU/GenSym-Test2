// $Revision: 9518 $ $Date: 2008-12-02 15:06:59 -0800 (Tue, 02 Dec 2008) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
//
// BullseyeCoverage run-time definitions for ARM RealView Compilation Tools

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define Libcov_covfile "/test.cov"

#include <stdio.h>
#include <stdlib.h>
#include <rt_sys.h>

#define O_CREAT OPEN_W
#define O_RDONLY OPEN_R
#define O_RDWR (OPEN_R | OPEN_PLUS | OPEN_B)
#define O_WRONLY OPEN_W
#define EINTR (-1)
#define ENOSYS (-2)
#define PATH_MAX FILENAME_MAX

#define errno Libcov_errno
int errno = 0;

#define S_IRUSR 0
#define S_IWUSR 0
int open(const char* path, int oflag, int mode)
{
	return _sys_open(path, oflag);
}

int close(int fildes)
{
	return _sys_close(fildes);
}

int read(int fildes, void* buf, unsigned nbyte)
{
	int n = -1;
	// _sys_read returns number of bytes not read
	int count = _sys_read(fildes, buf, nbyte, OPEN_B) & 0x7fffffff;
	if (count != -1) {
		count &= 0x7fffffff;
		n = nbyte - count;
	}
	return n;
}

int write(int fildes, const void* buf, unsigned nbyte)
{
	int n = -1;
	// _sys_write returns number of bytes not written
	const int count = _sys_write(fildes, buf, nbyte, OPEN_B);
	if (count >= 0) {
		n = nbyte - count;
	}
	return n;
}

#if !defined(off_t)
	typedef long off_t;
#endif

off_t lseek(int fildes, off_t offset, int whence)
{
	// SEEK_CUR not implemented
	if (whence == SEEK_END) {
		offset = _sys_flen(fildes) - offset;
	}
	return _sys_seek(fildes, offset);
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
