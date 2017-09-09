// $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
// Copyright (c) Bullseye Testing Technology
// Copyright (c) Sony Ericsson Mobile Communications AB/LTD/INC 2005,2007-2008
// This source file contains confidential proprietary information.

// BullseyeCoverage run-time definitions for Symbian OS on device.
// This file is not for the emulator. For the Symbian OS emulator we use the
// Windows library (libcov-windows-x86.lib) because:
//   1. The Windows library supports DLL entry point hooking. Auto-save cannot
//      be used in Symbian OS DLLs, so DLL entry point hooking is the only way
//      to automatically save coverage.
//   2. The Windows library conveniently accesses environment variables and
//      files on the host system rather than the emulated device.

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#define _UNICODE 1
#include <f32file.h>
#include "cmn-getenvBuf.h"

#if !defined(NULL)
	#define NULL 0
#endif
#define EINTR (-1)
#define ENOSYS (-2)
#define F_RDLCK 0
#define F_SETLKW 0
#define F_UNLCK 1
#define F_WRLCK 2
#define O_CREAT 0x0100
#define O_RDONLY 0
#define O_RDWR 2
#define O_WRONLY 1
#define PATH_MAX KMaxPath
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#define S_IRUSR 0x0100
#define S_IWUSR 0x0080
struct flock {
	short l_type;
	short l_whence;
	long l_start;
	long l_len;
};
typedef int off_t;
// Error codes are listed in e32err.h
static int errno;

struct FileDescriptor {
	RFs fs;
	RFile file;
};

static int open(const char* path, int oflag, int)
{
	int fildes = -1;
	unsigned fileMode = EFileRead;
	if ((oflag & (O_RDWR | O_WRONLY)) != 0) {
		fileMode = EFileWrite;
	}
	fileMode |= EFileStream | EFileShareAny;
	TPtrC8 pathNarrow(reinterpret_cast<const TUint8*>(path));
	RBuf pathWide;
	int err = KErrNoMemory;
	FileDescriptor* fd = new FileDescriptor;
	if (fd != NULL) {
		err = pathWide.Create(pathNarrow.Length());
	}
	if (err == 0) {
		pathWide.Copy(pathNarrow);
		err = fd->fs.Connect();
	}
	if (err == 0) {
		if ((oflag & O_CREAT) != 0) {
			err = fd->file.Create(fd->fs, pathWide, fileMode);
		}
		if ((oflag & O_CREAT) == 0 || err == KErrAlreadyExists) {
			err = fd->file.Open(fd->fs, pathWide, fileMode);
		}
	}
	pathWide.Close();
	if (err == 0) {
		fildes = int(fd);
	} else {
		fd->fs.Close();
		delete fd;
		errno = err;
	}
	return fildes;
}

static int close(int fildes)
{
	int status = 0;
	FileDescriptor* fd = reinterpret_cast<FileDescriptor*>(fildes);
	const int err = fd->file.Flush();
	if (err != 0) {
		status = 1;
		errno = err;
	}
	fd->fs.Close();
	delete fd;
	return status;
}

static int read(int fildes, void* buf, unsigned nbyte)
{
	int n;
	FileDescriptor* fd = reinterpret_cast<FileDescriptor*>(fildes);
	TPtr8 bufDes(static_cast<TUint8*>(buf), nbyte);
	const int err = fd->file.Read(bufDes, nbyte);
	if (err == 0) {
		n = bufDes.Length();
	} else {
		n = -1;
		errno = err;
	}
	return n;
}

static int write(int fildes, const void* buf, unsigned nbyte)
{
	int n = int(nbyte);
	TPtrC8 bufDes(static_cast<const TUint8*>(buf), nbyte);
	if (fildes == 2) {
		_LIT(msg, "BullseyeCoverage error");
		User::InfoPrint(msg);
		RDebug::Printf("%*s", nbyte, buf);
	} else {
		FileDescriptor* fd = reinterpret_cast<FileDescriptor*>(fildes);
		const int err = fd->file.Write(bufDes);
		if (err != 0) {
			n = -1;
			errno = err;
		}
	}
	return n;
}

static off_t lseek(int fildes, off_t offset, int whence)
{
	FileDescriptor* fd = reinterpret_cast<FileDescriptor*>(fildes);
	TSeek mode;
	switch (whence) {
	case SEEK_CUR:
		mode = ESeekCurrent;
		break;
	case SEEK_END:
		mode = ESeekEnd;
		break;
	case SEEK_SET:
	default:
		mode = ESeekStart;
		break;
	}
	const int err = fd->file.Seek(mode, offset);
	if (err != 0) {
		offset = -1;
		errno = err;
	}
	return offset;
}

static int fcntl(int fildes, int, struct flock* arg)
{
	int status = 0;
	FileDescriptor* fd = reinterpret_cast<FileDescriptor*>(fildes);
	int err;
	if (arg->l_type == F_UNLCK) {
		err = fd->file.UnLock(arg->l_start, arg->l_len);
	} else {
		while ((err = fd->file.Lock(arg->l_start, arg->l_len)) == KErrLocked) {
			// Wait 1/50 sec
			User::After(20000);
		}
	}
	if (err != 0) {
		status = -1;
		errno = err;
	}
	return status;
}

static char* getenv(const char* name)
{
	// Buffer containing return value
	static char buf[256];
	// Length of data read into buf
	static unsigned n;
	static int isOnce;
	if (!isOnce) {
		isOnce = true;
		RFs fs;
		RFile file;
		if (fs.Connect() == 0) {
			TDriveList driveList;
			if (fs.DriveList(driveList) == 0) {
				_LIT(envPath, " :\\BullseyeCoverageEnv.txt");
				TPtr path(reinterpret_cast<TText*>(buf), envPath().Length());
				path.Copy(envPath);
				for (unsigned i = 0; i < 26; i++) {
					if (driveList[i] != 0) {
						path[0] = char(i + 'a');
						if (file.Open(fs, path, EFileRead) == 0) {
							TPtr8 bufDes(reinterpret_cast<TUint8*>(buf), sizeof(buf) - 1);
							file.Read(bufDes);
							n = unsigned(bufDes.Length());
							break;
						}
					}
				}
			}
			fs.Close();
		}
	}
	return getenvBuf(name, buf, n);
}

#include <e32math.h>

struct timespec {
	long tv_sec;
	long tv_nsec;
};

static int nanosleep(const struct timespec* rqt, struct timespec*)
{
	User::After(rqt->tv_sec * 1000000 + rqt->tv_nsec / 1000);
	return 0;
}

#if Libcov_noAutoSave
	#include "stub-pthread.h"
#else
typedef TUint64 pthread_t;

static int pthread_create(
	pthread_t* thread,
	const void*,
	void* (* start_routine)(void*),
	void* arg)
{
	int err;
	TAutoClose<RThread> rthread;
	_LIT(kthread_name, "BullseyeCoverage0x");
	TBuf<KMaxKernelName> thread_name(kthread_name);
	do {
		thread_name.SetLength(kthread_name.BufferSize);
		thread_name.AppendNum(Math::Random(), EHex);
		err = rthread.iObj.Create(thread_name,
			reinterpret_cast<TThreadFunction>(start_routine),
			KDefaultStackSize, &User::Allocator(), arg);
	} while (err == KErrAlreadyExists);
	if (err == 0) {
		*thread = rthread.iObj.Id().Id();
		rthread.iObj.Resume();
	}
	return err;
}

static void pthread_exit(void* value_ptr)
{
	RThread().Kill(int(value_ptr));
}

static int pthread_join(pthread_t thread, void** value_ptr)
{
	TAutoClose<RThread> rthread;
	int status = rthread.iObj.Open(thread);
	if (status == 0) {
		TRequestStatus requestStatus;
		rthread.iObj.Logon(requestStatus);
		User::WaitForRequest(requestStatus);
		if (value_ptr) {
			*value_ptr = reinterpret_cast<void*>(requestStatus.Int());
		}
	}
	return status;
}
#endif // Libcov_noAutoSave

#if !defined(Libcov_covfile)
	#define Libcov_covfile "e:\\test.cov"
#endif
#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-atexit.h"
#include "stub-getcwd.h"
#include "cmn-autoSave.h"
#include "covrt.c"
