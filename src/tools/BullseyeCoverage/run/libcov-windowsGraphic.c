/* $Revision: 9519 $ $Date: 2008-12-02 15:14:31 -0800 (Tue, 02 Dec 2008) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Windows NT graphic subsystem
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <stdio.h>
#include <stdlib.h>
#define PATH_MAX _MAX_PATH
typedef long off_t;

#define WIN32 1
#define WINNT 1
#define _WIN32_WINNT 0x500
#if _M_IX86
	#define _X86_ 1
#elif _M_AMD64
	#define _AMD64_ 1
#elif _M_IA64
	#define _IA64_ 1
#endif
#include <stddef.h>
#include <ntddk.h>
#include <windef.h>
#include <winerror.h>
#include <wingdi.h>
#include <winddi.h>

// The one open file
static struct {
	HANDLE handle;
	char* memory;
	unsigned long offset;
	ULONG size;
} file;

#define Export __declspec(dllexport)

typedef BOOL (__stdcall* Function1)(
	SURFOBJ* p1,
	STROBJ* p2,
	FONTOBJ* p3,
	CLIPOBJ* p4,
	RECTL* p5,
	RECTL* p6,
	BRUSHOBJ* p7,
	BRUSHOBJ* p8,
	POINTL* p9,
	MIX p10);
typedef void (__stdcall* Function2)(SURFOBJ* p1, LONG p2, LONG p3, RECTL* p4);
typedef BOOL (__stdcall* Function3)(SURFOBJ* p1, POINTL* p2);
typedef BOOL (__stdcall* Function4)(SURFOBJ* p1, FLONG p2);
typedef void (__stdcall* Function5)(void);
typedef void (__stdcall* Function6)(DHPDEV p1, RECTL* p2);

static Function1 function_user1;
static Function2 function_user2;
static Function3 function_user3;
static Function4 function_user4;
static Function5 function_user5;
static Function6 function_user6;
static wchar_t ntGraphic_path[] = L"test.cov";

Export int __cdecl cov_write(void);

static BOOL __stdcall function_BullseyeCoverage1(
	SURFOBJ* p1,
	STROBJ* p2,
	FONTOBJ* p3,
	CLIPOBJ* p4,
	RECTL* p5,
	RECTL* p6,
	BRUSHOBJ* p7,
	BRUSHOBJ* p8,
	POINTL* p9,
	MIX p10)
{
	const BOOL s = function_user1(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	cov_write();
	return s;
}

static void __stdcall function_BullseyeCoverage2(SURFOBJ* p1, LONG p2, LONG p3, RECTL* p4)
{
	function_user2(p1, p2, p3, p4);
	cov_write();
}

static BOOL __stdcall function_BullseyeCoverage3(SURFOBJ* p1, POINTL* p2)
{
	const BOOL s = function_user3(p1, p2);
	cov_write();
	return s;
}

static BOOL __stdcall function_BullseyeCoverage4(SURFOBJ* p1, FLONG p2)
{
	const BOOL s = function_user4(p1, p2);
	cov_write();
	return s;
}

static void __stdcall function_BullseyeCoverage5(void)
{
	function_user5();
	cov_write();
}

static void __stdcall function_BullseyeCoverage6(DHPDEV p1, RECTL* p2)
{
	function_user6(p1, p2);
	cov_write();
}

extern int cov_graphicEntry;

BOOL __stdcall cov_DrvEnableDriver(ULONG version, ULONG size, DRVENABLEDATA* data)
{
	const BOOL success = DrvEnableDriver(version, size, data);
	if (success && size >= offsetof(DRVENABLEDATA, c) + sizeof(data->c) &&
		cov_graphicEntry)
	{
		unsigned i;
		for (i = 0; i < data->c; i++) {
			/* Video or printer driver */
			if (data->pdrvfn[i].iFunc == INDEX_DrvTextOut) {
				function_user1 = (Function1)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage1;
			}
			/* Video driver */
			if (data->pdrvfn[i].iFunc == INDEX_DrvMovePointer) {
				function_user2 = (Function2)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage2;
			}
			/* Printer driver (@Non-HP-Vancouver-om10.om.hp.com) */
			if (data->pdrvfn[i].iFunc == INDEX_DrvNextBand) {
				function_user3 = (Function3)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage3;
			}
			/* Printer driver */
			if (data->pdrvfn[i].iFunc == INDEX_DrvEndDoc) {
				function_user4 = (Function4)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage4;
			}
			if (data->pdrvfn[i].iFunc == INDEX_DrvDisableDriver) {
				function_user5 = (Function5)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage5;
			}
			if (data->pdrvfn[i].iFunc == INDEX_DrvSynchronize) {
				function_user6 = (Function6)data->pdrvfn[i].pfn;
				data->pdrvfn[i].pfn = (PFN)function_BullseyeCoverage6;
			}
		}
	}
	return success;
}

#include <winerror.h>
#undef errno
#define errno Libcov_errno
static int errno = 0;
#define EINTR ERROR_CANCELLED
#define ENOSYS ERROR_NOT_SUPPORTED

#define open(path, oflag, mode) Libcov_open()
static int Libcov_open(void)
{
	int fildes = 0;
	file.handle = EngLoadModuleForWrite(ntGraphic_path, 0);
	if (file.handle == NULL) {
		fildes = -1;
		errno = ERROR_OPEN_FAILED;
	} else {
		file.memory = EngMapModule(file.handle, &file.size);
		file.offset = 0;
	}
	return fildes;
}

static int close(int fildes)
{
	EngFreeModule(file.handle);
	return 0;
}

static int read(int fildes, void* buf, unsigned nbyte)
{
	unsigned n;
	char* buf_char = buf;
	for (n = 0; n < nbyte && file.offset < file.size; n++) {
		buf_char[n] = file.memory[file.offset++];
	}
	return (int)n;
}

static int write(int fildes, const void* buf, unsigned nbyte)
{
	unsigned n;
	if (fildes == 2) {
		// buf is nul terminated
		EngDebugPrint((char*)buf, "", NULL);
		n = nbyte;
	} else {
		const char* buf_char = buf;
		for (n = 0; n < nbyte && file.offset < file.size; n++) {
			file.memory[file.offset++] = buf_char[n];
		}
	}
	return (int)n;
}

static off_t lseek(int fildes, off_t offset, int whence)
{
	switch (whence) {
	case SEEK_CUR:
		file.offset += (unsigned long)offset;
		break;
	case SEEK_SET:
		file.offset = (unsigned long)offset;
		break;
	default:
		offset = -1;
		break;
	}
	return offset;
}

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-atexit.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "stub-getenv.h"
#include "stub-nanosleep.h"
#include "stub-pthread.h"
#include "cmn-autoSave.h"
#include "covrt.c"
