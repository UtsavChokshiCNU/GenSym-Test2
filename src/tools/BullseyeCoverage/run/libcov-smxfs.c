/* $Revision: 9490 $ $Date: 2008-11-25 16:51:58 -0800 (Tue, 25 Nov 2008) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions using smxFS
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include "smxfs.h"

#define EINTR (-1)
#define ENOSYS (-2)
#define O_CREAT 4
#define O_RDONLY 0
#define O_RDWR 2
#define O_WRONLY 1
#define PATH_MAX SFS_PATHFILENAME_LEN
#define SEEK_CUR SFS_SEEK_CUR
#define SEEK_END SFS_SEEK_END
#define SEEK_SET SFS_SEEK_SET
#define S_IRUSR 0
#define S_IWUSR 0
typedef long off_t;
static const int errno = 0;

static int open(const char* path, int oflag, int mode)
{
	int fd = -1;
	FILEHANDLE fh;
	const char* fmode = "r";
	if ((mode & (O_RDWR | O_WRONLY)) != 0) {
		fmode = "r+";
		if ((mode & O_CREAT) != 0) {
			fmode = "a";
		}
	}
	fh = sfs_fopen((char*)path, fmode);
	if (fh != NULL) {
		fd = (int)fh;
	}
	return fd;
}

static int close(int fildes)
{
	return sfs_fclose((FILEHANDLE)fildes);
}

static int read(int fildes, void* buf, unsigned nbyte)
{
	return (int)sfs_fread(buf, nbyte, 1, (FILEHANDLE)fildes);
}

static int write(int fildes, const void* buf, unsigned nbyte)
{
	int n = (int)sfs_fwrite((void*)buf, nbyte, 1, (FILEHANDLE)fildes);
	if (n == 0 && nbyte != 0) {
		n = -1;
	}
	return n;
}

static off_t lseek(int fildes, off_t offset, int whence)
{
	off_t pos = -1;
	if (sfs_fseek((FILEHANDLE)fildes, offset, whence) == 0) {
		pos = sfs_ftell((FILEHANDLE)fildes);
	}
	return pos;
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-getcwd.h"
#include "stub-getenv.h"
#include "stub-fcntl.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
