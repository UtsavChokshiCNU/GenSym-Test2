/* $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 *
 * BullseyeCoverage run-time definitions for Windows NT kernel mode
 */

#if _BullseyeCoverage
	#pragma BullseyeCoverage off
#endif

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#define PATH_MAX 128

#pragma comment(lib, "ntoskrnl.lib")
#define _WIN32_WINNT 0x500
#if _M_IX86
	#define _X86_ 1
#elif _M_AMD64
    #define _AMD64_ 1
#elif _M_IA64
	#define _IA64_ 1
#endif
#include <ntddk.h>

#undef off_t
#define off_t __int64

static struct {
	int isOpen;
	HANDLE handle;
	off_t offset;
} file[2];

static void (* DriverUnload_user)(DRIVER_OBJECT*);

void __cdecl cov_term(void);
extern NTSTATUS (__stdcall * cov_DriverEntry_user)(DRIVER_OBJECT*, UNICODE_STRING*);

/* The unload callback function.  */
static void DriverUnload(DRIVER_OBJECT* driverObject)
{
	/* Forward the call to user function */
	DriverUnload_user(driverObject);
	cov_term();
}

/* The entry point.
 * Command covlink replaces -entry:DriverEntry with -entry:cov_DriverEntry
 */
NTSTATUS cov_DriverEntry(DRIVER_OBJECT* driverObject, UNICODE_STRING* registry)
{
	const NTSTATUS status = cov_DriverEntry_user(driverObject, registry);
	if (NT_SUCCESS(status)) {
		/* If (and only if) there is a user unload function */
		if ((unsigned short)driverObject->Size == sizeof(*driverObject) &&
			driverObject->DriverUnload != 0)
		{
			/* Hook in our unload function */
			DriverUnload_user = driverObject->DriverUnload;
			driverObject->DriverUnload = DriverUnload;
		}
	} else {
		/* Shut down our autosave thread to avoid crash */
		cov_term();
	}
	return status;
}

#undef errno
#define errno Libcov_errno
static int errno = 0;
#define EINTR STATUS_CANCELLED
#define ENOSYS STATUS_NOT_SUPPORTED

#define getenv Libcov_getenv
static char* getenv(const char* name)
{
	static char buf[PATH_MAX];
	long status;
	UNICODE_STRING unicode;
	HANDLE key = NULL;
	OBJECT_ATTRIBUTES objectAttributes;
	wchar_t unicode_buf[PATH_MAX];
	unsigned long length;
	unsigned i;

	/* Open registry key of environment variables */
	RtlInitUnicodeString(&unicode,
		L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Session Manager\\Environment");
	InitializeObjectAttributes(&objectAttributes, &unicode,
		OBJ_CASE_INSENSITIVE, NULL, NULL);
	status = ZwOpenKey(&key, KEY_READ, &objectAttributes);

	if (status == 0) {
		/* Convert name to unicode */
		for (i = 0; name[i] != '\0'; i++) {
			unicode_buf[i] = (unsigned char)name[i];
		}
		unicode_buf[i] = L'\0';
		RtlInitUnicodeString(&unicode, unicode_buf);
	}

	if (status == 0) {
		/* Get value */
		struct {
			KEY_VALUE_FULL_INFORMATION info;
			wchar_t buf[PATH_MAX];
		} value_infoBuf;
		status = ZwQueryValueKey(key, &unicode, KeyValueFullInformation,
			&value_infoBuf, sizeof(value_infoBuf), &length);
		if (status == 0) {
			/* Convert value from unicode to buf */
			const wchar_t* value = (wchar_t*)((const char*)&value_infoBuf +
				value_infoBuf.info.DataOffset);
			for (i = 0; value[i] != L'\0'; i++) {
				buf[i] = (char)value[i];
			}
			buf[i] = '\0';
		}
	}
	if (key != NULL) {
		ZwClose(key);
	}
	return status == 0 ? buf : NULL;
}

/* Open the unicode filename prefix + path
 * Args
 *   fildes - file descriptor
 *   prefix - unicode
 *   path   - ASCII
 *   oflag  - ZwCreateFile parameter CreateDispostion
 */
static long open_unicode(
	int fildes,
	const wchar_t* prefix,
	const char* path,
	unsigned long oflag)
{
	unsigned i;
	unsigned j;
	UNICODE_STRING unicode;     /* prefix + path */
	wchar_t unicode_buf[PATH_MAX * sizeof(wchar_t)];
	OBJECT_ATTRIBUTES objectAttributes;
	IO_STATUS_BLOCK statusBlock;

	/* unicode_buf = prefix */
	for (i = 0; prefix[i] != L'\0'; i++) {
		unicode_buf[i] = prefix[i];
	}

	/* unicode_buf += path */
	for (j = 0; path[j] != '\0'; j++) {
		unicode_buf[i + j] = (wchar_t)(unsigned char)path[j];
	}
	unicode_buf[i + j] = L'\0';

	RtlInitUnicodeString(&unicode, unicode_buf);

	/* Open */
	InitializeObjectAttributes(&objectAttributes, &unicode,
		OBJ_CASE_INSENSITIVE, NULL, NULL);
	return ZwCreateFile(&file[fildes].handle,
		GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE, &objectAttributes,
		&statusBlock, NULL, FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, oflag,
		FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
}

#define open(path, oflag, mode) Libcov_open(path, oflag)
static int Libcov_open(const char* path, int oflag)
{
	int fildes = -1;
	long status = STATUS_INSUFFICIENT_RESOURCES;
	unsigned char drive;

	if (!file[0].isOpen) {
		fildes = 0;
	} else if (!file[1].isOpen) {
		fildes = 1;
	}
	if (oflag & O_CREAT) {
		oflag = FILE_OPEN_IF;
	} else {
		oflag = FILE_OPEN;
	}
	if (fildes >= 0) {
		file[fildes].offset = 0;
		status = open_unicode(fildes, L"\\??\\", path, (unsigned)oflag);
	}
	/* If failure could be due to lack of device name mappings */
	if (status == STATUS_OBJECT_PATH_NOT_FOUND && path[1] == ':') {
		/* Try all partitions, 1-9 */
		for (drive = '1'; drive <= '9' && status != 0; drive++) {
			/* Construct prefix for the partition */
			static wchar_t prefix[] = L"\\Device\\Harddisk0\\PartitionN";
			const unsigned last = sizeof(prefix) / sizeof(prefix[0]) - 2;
			prefix[last] = drive;
			/* Open with prefix and without drive specifier */
			status = open_unicode(fildes, prefix, path + 2, (unsigned)oflag);
		}
	}
	/* If failure due to UNC prefix */
	if (status != 0 && path[0] == '\\' && path[1] == '\\') {
		status = open_unicode(fildes, L"\\Device\\LanmanRedirector", path + 1, (unsigned)oflag);
	}
	if (status == 0) {
		file[fildes].isOpen = 1;
	} else {
		fildes = -1;
		errno = (int)status;
	}
	return fildes;
}

static int close(int fildes)
{
	int status = (int)ZwClose(file[fildes].handle);
	file[fildes].isOpen = 0;
	if (status != 0) {
		errno = (int)status;
	}
	return status;
}

static int read(int fildes, void* buf, unsigned nbyte)
{
	int n;
	IO_STATUS_BLOCK statusBlock;
	long status = ZwReadFile(file[fildes].handle, NULL, NULL, NULL,
		&statusBlock, buf, nbyte,
		(LARGE_INTEGER*)&file[fildes].offset, NULL);
	if (status == 0) {
		n = (int)statusBlock.Information;
		file[fildes].offset += n;
	} else {
		n = -1;
		errno = (int)status;
	}
	return n;
}

static int write(int fildes, const void* buf, unsigned nbyte)
{
	int n;
	if (fildes == 2) {
		DbgPrint("%s", buf);
		n = nbyte;
	} else {
		IO_STATUS_BLOCK statusBlock;
		long status = ZwWriteFile(file[fildes].handle, NULL, NULL, NULL,
			&statusBlock, (void*)buf, nbyte,
			(LARGE_INTEGER*)&file[fildes].offset, NULL);
		if (status == 0) {
			n = (int)statusBlock.Information;
			file[fildes].offset += n;
		} else {
			n = -1;
			errno = (int)status;
		}
	}
	return n;
}

static off_t lseek(int fildes, off_t offset, int whence)
{
	FILE_STANDARD_INFORMATION info;
	IO_STATUS_BLOCK statusBlock;
	switch (whence) {
	case SEEK_SET:
		file[fildes].offset = offset;
		break;
	case SEEK_CUR:
		file[fildes].offset += offset;
		break;
	case SEEK_END:
		if (ZwQueryInformationFile(file[fildes].handle, &statusBlock,
			&info, sizeof(info), FileStandardInformation) == 0)
		{
			file[fildes].offset = info.EndOfFile.QuadPart + offset;
		} else {
			file[fildes].offset = -1;
		}
		break;
	default:
		file[fildes].offset = -1;
		break;
	}
	return file[fildes].offset;
}

struct timespec {
	long tv_sec;
	long tv_nsec;
};

static int nanosleep(const struct timespec* rqt, struct timespec* rmt)
{
	LARGE_INTEGER largeInteger;
	largeInteger.QuadPart = -(rqt->tv_sec * 10000000 + rqt->tv_nsec / 100);
	KeDelayExecutionThread(KernelMode, 0, &largeInteger);
	rmt = rmt;
	return 0;
}

#include <ntddk.h>
#define PTHREAD_LINK __stdcall

typedef HANDLE pthread_t;

#define pthread_create(thread, attr, start_routine, arg) \
	(int)PsCreateSystemThread(thread, THREAD_ALL_ACCESS, NULL, \
	NULL, NULL, (PKSTART_ROUTINE)start_routine, arg)
#define pthread_exit(status) PsTerminateSystemThread((long)(intptr_t)(status))
static int pthread_join(pthread_t thread, void** value_ptr)
{
	void* object;
	NTSTATUS status = ObReferenceObjectByHandle(thread, THREAD_ALL_ACCESS,
		NULL, KernelMode, &object, NULL);
	if (status == 0) {
		status = KeWaitForSingleObject(object, Executive, KernelMode,
			FALSE, NULL);
	}
	value_ptr = value_ptr;
	return (int)status;
}

#if _M_AMD64
// Avoid LNK2005 on KeGetCurrentIrql
#define KeGetCurrentIrql libcov_KeGetCurrentIrql
static __inline KIRQL KeGetCurrentIrql()
{
	return (KIRQL)__readcr8();
}
#endif
#define isReady() (KeGetCurrentIrql() == PASSIVE_LEVEL)

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "stub-atexit.h"
#include "stub-fcntl.h"
#include "stub-getcwd.h"
#include "cmn-autoSave.h"
#include "covrt.c"
