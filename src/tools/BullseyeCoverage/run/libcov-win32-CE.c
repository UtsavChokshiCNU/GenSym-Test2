/* $Revision: 9609 $ $Date: 2009-01-08 17:31:04 -0800 (Thu, 08 Jan 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 * Modifying this source file is not recommended because this may interfere with
 * upgrading to a future release. If you need changes, contact Technical Support.
 *
 * This source contains definitions for Windows CE
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#if _M_ARM
	#define ARM
	#define _ARM_
#elif _M_IX86
	#define _X86_
	#define x86 1
#elif _M_MRX000
	#define MIPS
	#define _MIPS_
#elif _M_SH == 4
	#define SHx
	#define _SHX_
#else
	#error This platform not supported
#endif

#include <limits.h>
#define PATH_MAX _MAX_PATH
#define UNDER_CE 1
#define UNICODE 1
#define _UNICODE 1
#include <windows.h>
#define LOCKFILE_FAIL_IMMEDIATELY 0x00000001
#define LOCKFILE_EXCLUSIVE_LOCK   0x00000002

#define O_CREAT 0x0100
#define O_RDONLY 0
#define O_RDWR 0x0002
#define O_WRONLY 0x0001

// Write a string to standard error
// The string is nul-terminated, length parameter is redundant
static void write_stderr(const char* string, unsigned length)
{
	unsigned i;
	wchar_t buf[256];
	for (i = 0; i < length && i < sizeof(buf) / sizeof(buf[0]); i++) {
		buf[i] = (unsigned char)string[i];
	}
	buf[i] = L'\0';
	OutputDebugString(buf);
	MessageBox(NULL, buf, L"BullseyeCoverage", (int)(MB_ICONSTOP | MB_OK | MB_SETFOREGROUND));
}

#include "win32-dynamic.h"
#include "libcov-win32.h"
#include "cmn-getenvFile.h"

#pragma comment(lib, "coredll.lib")

static int fcntl(int fildes, int cmd, const struct flock* arg)
{
	int success = 1;
	static HMODULE module = NULL;
	typedef BOOL (__stdcall* Lock)(HANDLE, DWORD, DWORD, DWORD, DWORD, OVERLAPPED*);
	typedef BOOL (__stdcall* Unlk)(HANDLE, DWORD, DWORD, DWORD, OVERLAPPED*);
	static Lock lock = NULL;
	static Unlk unlk = NULL;
	if (module == NULL) {
		module = GetModuleHandle(L"coredll.dll");
		if (module != NULL) {
			lock = (Lock)GetProcAddress(module, L"LockFileEx");
			unlk = (Unlk)GetProcAddress(module, L"UnlockFileEx");
		}
	}
	if (lock != NULL && unlk != NULL) {
		const HANDLE handle = fileList[fildes].handle;
		OVERLAPPED overlapped;
		overlapped.Offset = (unsigned long)arg->l_start;
		overlapped.OffsetHigh = 0;
		overlapped.hEvent = NULL;
		if (arg->l_type == F_UNLCK) {
			success = unlk(handle, 0, (unsigned long)arg->l_len, 0, &overlapped);
		} else {
			unsigned flag = 0;
			if (cmd == F_SETLK) {
				flag |= LOCKFILE_FAIL_IMMEDIATELY;
			}
			if (arg->l_type == F_WRLCK) {
				flag |= LOCKFILE_EXCLUSIVE_LOCK;
			}
			success = lock(handle, flag, 0, (unsigned long)arg->l_len, 0, &overlapped);
			if (!success && GetLastError() == ERROR_NOT_SUPPORTED) {
				lock = NULL;
				success = 1;
			}
		}
		if (!success) {
			errno = (int)GetLastError();
		}
	}
	return success ? 0 : -1;
}

#define getcwd Libcov_getcwd
static char* getcwd(char* buf, unsigned size)
{
	return "\\";
}

static char* getenv(const char* name)
{
	return getenvFile(name, "\\BullseyeCoverageEnv.txt");
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "libcov-win32-dynamic.h"
#include "cmn-autoSave.h"
#include "covrt.c"
