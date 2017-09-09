/* $Revision$ $Date: 2009-12-18 18:06:41 -0800 (Fri, 18 Dec 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 * Do not modify this source file.  If you need changes, contact Technical Support.
 * Modification is likely to break functionality and interfere with upgrading to a future release.
 *
 * This source contains definitions specific to the static library part of the dynamic configuration.
 */

#if _M_AMD64
	#include "win32-dynamic-bin-x64.h"
#elif _M_ARM && _M_ARMT
	#include "win32-dynamic-bin-armv4i.h"
#elif _M_ARM
	#include "win32-dynamic-bin-arm.h"
#elif _M_IA64
	#include "win32-dynamic-bin-ia64.h"
#elif _M_IX86 && UNDER_CE
	#include "win32-dynamic-bin-x86ce.h"
#elif _M_IX86
	#include "win32-dynamic-bin-x86.h"
#elif _M_MRX000
	#include "win32-dynamic-bin-mips.h"
#elif _M_SH == 4
	#include "win32-dynamic-bin-sh4.h"
#else
	#error
#endif

#define Libcov_dynamic 1

static AtexitParameter dllAtexitParameter;
static const Dynamic* dynamic;
static int isDll = 0;
static StaticImage staticImage = { libcovMagic, cov_write, fileList };

/* Create and load the dynamic run-time */
static int loadDynamic()
{
	int status = 0;
	HINSTANCE instance;
	_TCHAR path[PATH_MAX];
	// Get path for win32-dynamic-bin-*.dll
	#if UNDER_CE
		// Loading this DLL from the temp directory crashes on the emulator 4.2
		unsigned length = 1;
		path[0] = _T('\\');
	#else
		unsigned length = (unsigned)GetTempPath(PATH_MAX, path);
		if (length == 0) {
			path[0] = _T('c');
			path[1] = _T(':');
			length = 2;
		}
	#endif
	if (path[length - 1] != _T('\\')) {
		path[length] = _T('\\');
		length++;
	}
	lstrcpy(path + length, dll_basename);
	// Attempt to load the DLL
	//   When LoadLibrary fails to find the DLL under eMbedded Visual
	//   C++ 3, the debugger displays a dialog box to browse for it.
	//   So we check for existence before calling LoadLibrary
	if (GetFileAttributes(path) == 0xffffffff) {
		instance = NULL;
	} else {
		instance = LoadLibrary(path);
	}
	if (instance == NULL) {
		HANDLE fd;
		unsigned i;
		status = (int)GetLastError();
		// Create it now
		fd = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fd != INVALID_HANDLE_VALUE) {
			char zero[128];
			DWORD unused;
			unsigned i;
			// This loop goes two at a time to avoid being optimized into a call to memset
			for (i = 0; i < sizeof(zero); i += 2) {
				zero[i] = 0;
				zero[i + 1] = 0;
			}
			for (i = 0; i < sizeof(dll_image); ) {
				const unsigned m = dll_image[i] & 0x7f;
				if (dll_image[i] >= 0x80) {
					i++;
					WriteFile(fd, dll_image + i, m, &unused, NULL);
					i += m;
				} else {
					WriteFile(fd, zero, m, &unused, NULL);
					i++;
				}
			}
			CloseHandle(fd);
			#if !UNDER_CE
				// Schedule deletion upon reboot
				MoveFileEx(path, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
			#endif
		}
		// Re-attempt load for a while
		for (i = 0; i < 10; i++) {
			instance = LoadLibrary(path);
			if (instance != NULL) {
				status = 0;
				break;
			}
			// Yield CPU and try again later
			Sleep(10);
		}
	}
	// Register
	if (status == 0) {
		typedef const Dynamic* (__cdecl* Init)(void);
		const Init init = (Init)GetProcAddress(instance, _T("init"));
		if (init == NULL) {
			status = (int)GetLastError();
		} else {
			const char* p = getenv("COVAUTOSAVE");
			dynamic = init();
			status = dynamic->staticImageAdd(&staticImage);
			if (p == NULL || p[0] != '0' || p[1] != '\0') {
				dynamic->createAutoSave();
			}
		}
	}
	return status;
}

#define atexit Libcov_atexit
static int atexit(AtexitParameter atexitParameter)
{
	const int status = loadDynamic();
	if (isDll) {
		dllAtexitParameter = atexitParameter;
	} else {
		if (status == 0) {
			staticImage.exeAtexitParameter = atexitParameter;
		}
	}
	if (status != 0) {
		errno = status;
	}
	return status;
}

#if __cplusplus
extern "C"
#else
extern
#endif
BOOL (__stdcall* cov_DllMain_user)(HANDLE, DWORD, void*);

#if __cplusplus
extern "C"
#endif
BOOL __stdcall cov_DllMain(HINSTANCE instance, DWORD why, void* p)
{
	BOOL success = 1;
	if (why == DLL_PROCESS_ATTACH) {
		isDll = 1;
		module = instance;
	}
	if (why == DLL_PROCESS_DETACH && dynamic != NULL) {
		// Call processDetach before user DllMain which could have a call to cov_term.
		dynamic->staticImageRemove(&staticImage);
	}
	if (cov_DllMain_user != 0) {
		success = cov_DllMain_user(instance, why, p);
	}
	if (why == DLL_PROCESS_DETACH && dllAtexitParameter != NULL) {
		dllAtexitParameter();
	}
	return success;
}
