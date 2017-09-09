/* $Revision: 9490 $ $Date: 2008-11-25 16:51:58 -0800 (Tue, 25 Nov 2008) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 * Modifying this source file is not recommended because this may interfere with
 * upgrading to a future release. If you need changes, contact Technical Support.
 *
 * This source contains definitions for Windows NT
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#if __BORLANDC__
	#pragma comment(lib, "import32.lib")
	#pragma option -w-par
#endif
#if __CYGWIN__
	#define _WIN32 1
#endif
#if _MSC_VER
	#pragma comment(lib, "kernel32.lib")
	#pragma comment(lib, "user32.lib")
	/* Needed for the Symbian OS emulator */
	#pragma data_seg(".covdata")
	#pragma warning(disable: 4100)  /* unreferenced formal parameter */
	#pragma warning(disable: 4115)  /* named type definition in () */
	#pragma warning(disable: 4201)  /* nameless struct/union */
	#pragma warning(disable: 4209)  /* typedef redefinition */
	#pragma warning(disable: 4214)  /* bit field types other than int */
	#pragma warning(disable: 4514)  /* unreferenced inline function */
	#pragma warning(disable: 4996)
#endif

#define WIN32_LEAN_AND_MEAN /* Avoid Borland C++ 5.5 uuid.lib */
#define _WIN32_WINNT 0x500
#include <windows.h>

static void write_stderr(const char* string, unsigned length);

#include "win32-dynamic.h"
#include "libcov-win32.h"

static int fcntl(int fildes, int cmd, const struct flock* arg)
{
	int success;
	const HANDLE handle = fileList[fildes].handle;
	OVERLAPPED overlapped;
	overlapped.Offset = (unsigned long)arg->l_start;
	overlapped.OffsetHigh = 0;
	overlapped.hEvent = NULL;
	if (arg->l_type == F_UNLCK) {
		success = UnlockFileEx(handle, 0, (unsigned long)arg->l_len,
			0, &overlapped);
	} else {
		unsigned flag = 0;
		if (cmd == F_SETLK) {
			flag |= LOCKFILE_FAIL_IMMEDIATELY;
		}
		if (arg->l_type == F_WRLCK) {
			flag |= LOCKFILE_EXCLUSIVE_LOCK;
		}
		success = LockFileEx(handle, flag, 0, (unsigned long)arg->l_len,
			0, &overlapped);
	}
	if (!success) {
		errno = (int)GetLastError();
	}
	return success ? 0 : -1;
}

#define getcwd Libcov_getcwd
static char* getcwd(char* buf, unsigned size)
{
	if (GetCurrentDirectory(size, buf) == 0) {
		errno = (int)GetLastError();
		buf = NULL;
	}
	return buf;
}

/* Do not use Windows API for getenv with Cygwin.  Reference: CW_SYNC_WINENV */
#if !__GNUC__
/*lint -e683 */
#define getenv Libcov_getenv
static char* getenv(const char* name)
{
	char* value = NULL;
	/* Use GetEnvironmentStrings because it does not require allocating a buffer like GetEnvironmentVariable does */
	const unsigned length = lstrlen(name);
	char* p;
	for (p = GetEnvironmentStrings(); p != NULL && *p != '\0'; p++) {
		/* Compare name with the string beginning at p */
		/*   Windows does not provide a convenient API to do this */
		unsigned i;
		for (i = 0; i < length; i++) {
			char c = *p++;
			if (c >= 'a' && c <= 'z') {
				c -= 'a' - 'A';
			}
			if (name[i] != c) {
				break;
			}
		}
		if (i == length && *p == '=') {
			value = p + 1;
			break;
		}
		do {
			p++;
		} while (*p != '\0');
	}
	return value;
}
#endif

/* Determine whether the current process is a console program versus GUI */
static int isConsole(void)
{
	int is = 0;
	const HMODULE module = GetModuleHandle(NULL);
	const IMAGE_DOS_HEADER* imageDosHeader = (IMAGE_DOS_HEADER*)module;
	if (imageDosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
		const IMAGE_NT_HEADERS* imageNtHeaders =
			(IMAGE_NT_HEADERS*)((char*)module + imageDosHeader->e_lfanew);
		if (imageNtHeaders->Signature == IMAGE_NT_SIGNATURE) {
			is = imageNtHeaders->OptionalHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI;
		}
	}
	return is;
}

// Write a string to standard error
// The string is nul-terminated, length parameter is redundant
static void write_stderr(const char* string, unsigned length)
{
	char buf[2048];
	char path[PATH_MAX];
	// Add executable path to message
	GetModuleFileName(module, path, sizeof(path));
	lstrcpy(buf, string);
	lstrcpy(buf + length - 1, ". Executable is ");
	lstrcat(buf, path);
	lstrcat(buf, "\n");
	if (isConsole()) {
		// Write the message to standard error
		DWORD unused;
		WriteFile(GetStdHandle(STD_ERROR_HANDLE), buf, (unsigned)lstrlen(buf), &unused, NULL);
	} else {
		static const char help[] = "\nFor details, see BullseyeCoverage Help topic Troubleshooting: Run-time: Errors 1-99";
		lstrcat(buf, help);
		// Display the message with MessageBox
		MessageBox(NULL, buf, "BullseyeCoverage",
			MB_SERVICE_NOTIFICATION |
			MB_DEFBUTTON2 |
			MB_ICONSTOP |
			MB_SETFOREGROUND |
			MB_TASKMODAL);
	}
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#if _MSC_VER
	#include "libcov-win32-dynamic.h"
#else
	#include "libcov-win32-static.h"
#endif
#include "cmn-autoSave.h"
#include "covrt.c"
