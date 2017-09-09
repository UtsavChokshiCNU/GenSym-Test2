/* $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for user-defined operating system
 * http://www.bullseye.com/help/env_custom.html
 * Implementations should conform to the Single UNIX Specification
 * http://www.opengroup.org/onlinepubs/009695399/
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

/*---------------------------------------------------------------------------
// Miscellaneous types and constants
*/
#if 1
	#include <stdlib.h>
#else
	#define NULL 0
#endif

#if 1
	#include <limits.h>
	#if !defined(PATH_MAX)
		#error PATH_MAX not defined
	#endif
#else
	/* Maximum number of bytes in a pathname, including the terminating null character. */
	#define PATH_MAX 128
#endif

#if 1
	#include <sys/types.h>
	enum { compileTimeCheck_off_t = sizeof(off_t) };
#else
	/* Used for file sizes. */
	typedef long off_t;
#endif

/*---------------------------------------------------------------------------
// errno
// This variable and at least the errors listed below must be defined.
//   EINTR - Interrupted function
//   ENOSYS - Function not supported
// Assign an error code to errno whenever one of the functions in this file fails.
// This information is only used for diagnostics, so the particular error values are not important.
// If a function fails but does not set errno=ENOSYS, BullseyeCoverage reports a run-time error.
*/
#if 1
	#include <errno.h>
	#if !defined(EINTR)
		#define EINTR (-1)
	#endif
	#if !defined(ENOSYS)
		#define ENOSYS (-2)
	#endif
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/errno.html */
	int errno = 0;
	#define EINTR (-1)
	#define ENOSYS (-2)
#endif

/*---------------------------------------------------------------------------
// fcntl
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <fcntl.h>
	enum { compileTimeCheck_flock = sizeof(struct flock) };
	#if !defined(F_SETLKW)
		#error F_SETLKW not defined
	#endif
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/fcntl.html */
	struct flock {
		short l_type;
		short l_whence;
		long l_start;
		long l_len;
	};
	#define F_SETLKW 0
	#define F_RDLCK 0
	#define F_UNLCK 1
	#define F_WRLCK 2

	int fcntl(int fildes, int cmd, struct flock* arg)
	{
		/* Successful return is 0 */
		errno = ENOSYS;
		return -1;
	}
#endif

/*---------------------------------------------------------------------------
// open, close, read, write, lseek
// These functions be defined.
*/
#if 1
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#if !defined(O_CREAT)
		#error O_CREAT not defined
	#endif
	#if !defined(S_IRUSR)
		#error S_IRUSR not defined
	#endif
	#if !defined(SEEK_CUR)
		#error SEEK_CUR not defined
	#endif
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/open.html
	// http://www.opengroup.org/onlinepubs/009695399/functions/close.html
	// http://www.opengroup.org/onlinepubs/009695399/functions/read.html
	// http://www.opengroup.org/onlinepubs/009695399/functions/write.html
	// http://www.opengroup.org/onlinepubs/009695399/functions/lseek.html
	*/
	#define O_CREAT 0x0100
	#define O_RDONLY 0
	#define O_RDWR 2
	#define O_WRONLY 1
	#define S_IRUSR 0x0100
	#define S_IWUSR 0x0080
	#define SEEK_CUR 1
	#define SEEK_END 2
	#define SEEK_SET 0

	int open(const char* path, int oflag, int mode)
	{
		/* Successful return is > 2 */
		errno = ENOSYS;
		return -1;
	}

	int close(int fildes)
	{
		/* Successful return is 0 */
		errno = ENOSYS;
		return 1;
	}

	int read(int fildes, void* buf, unsigned nbyte)
	{
		/* Successful return is number of bytes read >= 0 */
		errno = ENOSYS;
		return -1;
	}

	int write(int fildes, const void* buf, unsigned nbyte)
	{
		if (fildes == 2) {
			/* Report the error message in buf.  The message is nul-terminated and the length of the message is nbyte.
			// This is critical. Implement this first.
			*/
			#error Error reporting unimplemented
			/* fputs(buf, stderr); */
		} else {
			/* Write to file */
		}
		/* Successful return is number of bytes written >= 0 */
		errno = ENOSYS;
		return -1;
	}

	off_t lseek(int fildes, off_t offset, int whence)
	{
		/* Successful return is >= 0 */
		errno = ENOSYS;
		return -1;
	}
#endif

/*---------------------------------------------------------------------------
// atexit
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <stdlib.h>
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/atexit.html */
	int atexit(void (*function)(void))
	{
		/* Successful return is 0 */
		errno = ENOSYS;
		return 1;
	}
#endif

/*---------------------------------------------------------------------------
// getcwd
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <unistd.h>
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/getcwd.html */
	char* getcwd(char* buf, unsigned size)
	{
		errno = ENOSYS;
		/* Successful return is buf */
		return NULL;
	}
#endif

/*---------------------------------------------------------------------------
// getenv
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <stdlib.h>
#else
	/* http://www.opengroup.org/onlinepubs/009695399/functions/getenv.html */
	char* getenv(const char* name)
	{
		return NULL;
	}
#endif

/*---------------------------------------------------------------------------
// nanosleep
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <time.h>
	enum { compileTimeCheck_timespec = sizeof(struct timespec) };
#else
	struct timespec {
		long tv_sec;
		long tv_nsec;
	};

	int nanosleep(const struct timespec* rqt, struct timespec* rmt)
	{
		/* Successful return is 0 */
		errno = ENOSYS;
		return -1;
	}
#endif

/*---------------------------------------------------------------------------
// pthread_create, pthread_exit, pthread_join
// This function is optional; "#if 0" is OK
*/
#if 1
	#include <pthread.h>
#else
	typedef int pthread_t;

	int pthread_create(pthread_t* thread, const void* attr, void* (* start_routine)(void*), void* arg)
	{
		/* Successful return is 0 */
		/* Upon failure return an error number rather than setting errno */
		return ENOSYS;
	}

	void pthread_exit(void* value_ptr)
	{
	}

	int pthread_join(pthread_t thread, void** value_ptr)
	{
		/* Successful return is 0 */
		/* Upon failure return an error number rather than setting errno */
		return ENOSYS;
	}
#endif

/*---------------------------------------------------------------------------
// BullseyeCoverage run-time code
*/
#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "cmn-autoSave.h"
#include "covrt.c"
