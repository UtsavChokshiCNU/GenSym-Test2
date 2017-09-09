/* $Revision: 9519 $ $Date: 2008-12-02 15:14:31 -0800 (Tue, 02 Dec 2008) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 * Modifying this source file is not recommended because this may interfere with
 * upgrading to a future release. If you need changes, contact Technical Support.
 *
 * This source contains definitions common to Windows NT and Windows CE
 */

#include <limits.h>
#if __CYGWIN__
	#define _T __TEXT
#else
	#include <tchar.h>
#endif
#if !PATH_MAX
	#define PATH_MAX _MAX_PATH
#endif

#if !__GNUC__
	typedef long off_t;
#endif

#if !defined(F_SETLK)
	#define F_SETLK 0
	#define F_SETLKW 1
	#define F_RDLCK 0
	#define F_WRLCK 1
	#define F_UNLCK 2
	struct flock {
		short l_type;
		short l_whence;
		off_t l_start;
		off_t l_len;
	};
#endif

#undef errno
#define errno Libcov_errno
static int errno = 0;
#undef EINTR
#undef ENOSYS
#define EINTR ERROR_CANCELLED
#define ENOSYS ERROR_NOT_SUPPORTED

static FileDescriptor fileList[fileListSize];

static HMODULE module = NULL;

#define open(path, oflag, mode) Libcov_open(path, oflag)
static int Libcov_open(const char* path, int oflag)
{
	int fildes;
	for (fildes = (int)sizeof(fileList) / sizeof(fileList[0]) - 1; fildes >= 0; fildes--) {
		if (fildes == 2) {
			// Reserved for standard error
			continue;
		}
		if (InterlockedExchange(&fileList[fildes].lock, 1) == 0) {
			break;
		}
	}
	if (fildes < 0) {
		errno = ERROR_TOO_MANY_OPEN_FILES;
	} else {
		unsigned retry;
		unsigned lastError = 0;

		#if defined(UNICODE)
			/* Windows CE */
			wchar_t path_native[PATH_MAX];
			unsigned i;
			for (i = 0;; i++) {
				path_native[i] = (unsigned char)path[i];
				if (path[i] == 0) {
					break;
				}
			}
			path_native[i] = L'\0';
		#else
			/* Windows 9x */
			const char* path_native = path;
		#endif
		if (oflag & O_CREAT) {
			oflag = OPEN_ALWAYS;
		} else {
			oflag = OPEN_EXISTING;
		}
		// Try to open file, once every 0.2 seconds for up to 1 minute
		for (retry = 0; retry < 5 * 60; retry++) {
			fileList[fildes].handle = CreateFile(path_native,
				GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL, (unsigned)oflag, FILE_ATTRIBUTE_NORMAL, NULL);
			if (fileList[fildes].handle != INVALID_HANDLE_VALUE) {
				break;
			}
			lastError = GetLastError();
			if (lastError != ERROR_SHARING_VIOLATION) {
				break;
			}
			// Sharing violation probably means file is being copied,
			//   wait a bit and try again.
			Sleep(200);
		}
		if (fileList[fildes].handle == INVALID_HANDLE_VALUE) {
			fileList[fildes].lock = 0;
			fildes = -1;
			errno = (int)lastError;
		}
	}
	return fildes;
}

#define close Libcov_close
static int close(int fildes)
{
	int success;
	success = CloseHandle(fileList[fildes].handle);
	fileList[fildes].lock = 0;
	if (!success) {
		errno = (int)GetLastError();
	}
	return success ? 0 : 1;
}

#define read Libcov_read
static int read(int fildes, void* buf, unsigned nbyte)
{
	DWORD n;
	if (!ReadFile(fileList[fildes].handle, buf, nbyte, &n, NULL)) {
		n = (DWORD)-1;
		errno = (int)GetLastError();
	}
	return (int)n;
}

#define write Libcov_write
static int write(int fildes, const void* buf, unsigned nbyte)
{
	DWORD n;
	if (fildes == 2) {
		write_stderr((const char*)buf, nbyte);
		n = nbyte;
	} else {
		if (!WriteFile(fileList[fildes].handle, buf, nbyte, &n, NULL)) {
			n = (DWORD)-1;
			errno = (int)GetLastError();
		}
	}
	return (int)n;
}

#define lseek Libcov_lseek
static off_t lseek(int fildes, off_t offset, int whence)
{
	// assert(SEEK_SET     == FILE_BEGIN);
	// assert(SEEK_CURRENT == FILE_CURRENT);
	// assert(SEEK_END     == FILE_END);
	off_t new_ = (off_t)SetFilePointer(fileList[fildes].handle, offset, NULL, (unsigned)whence);
	if (new_ == -1) {
		errno = (int)GetLastError();
	}
	return new_;
}

#if __CYGWIN__
	#define nanosleep nanosleep1
	#define pthread_t pthread_t1
	#define fcntl fcntl1
#else
	struct timespec {
		unsigned long tv_sec;
		unsigned long tv_nsec;
	};
#endif

static int nanosleep(const struct timespec* rqt, struct timespec* rmt)
{
	Sleep(rqt->tv_sec * 1000 + rqt->tv_nsec / 1000000);
	rmt = rmt;
	return 0;
}
