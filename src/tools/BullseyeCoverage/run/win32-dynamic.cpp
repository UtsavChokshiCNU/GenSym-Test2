// $Revision: 10767 $ $Date: 2010-01-20 14:15:27 -0800 (Wed, 20 Jan 2010) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
// Do not modify this source file.  If you need changes, contact Technical Support.
// Modification is likely to break functionality and interfere with upgrading to a future release.
//
// This DLL implements atexit for EXEs, the auto-save thread, and process termination handling.
// This "dynamic" run-time configuration is used with the compilers below running on Windows CE and Windows NT.
//   Intel C++
//   Microsoft C++
//   Nokia CodeWarrior (Symbian OS emulator)

#if _M_ARM
	#define ARM
	#define _ARM_
	#define UNDER_CE 1
#elif _M_IX86
	#define _X86_
	#define x86 1
#elif _M_MRX000
	#define MIPS
	#define _MIPS_
	#define UNDER_CE 1
#elif _M_SH
	#define SHx
	#define _SHX_
	#define UNDER_CE 1
#endif
#define WIN32_LEAN_AND_MEAN
#if UNDER_CE
	#define WINCEMACRO
	#define UNICODE 1
#endif
#include <windows.h>

#define Libcov_interface 3
#include "atomic.h"
#include "libcov.h"
#include "win32-dynamic.h"

#define sizeofarray(a) (sizeof(a) / sizeof(a[0]))

// Locks for adding to and removing from staticImageList.
// Simultaneous 'add' operations need synchronization because multiple threads may simultaneously
// find the same unused slot.  The 'remove' operation needs no synchronization because the addresses
// removed are unique and cannot conflict.  The auto-save thread and 'remove' operation need
// synchronization to prevent auto-save from accessing data removed while it is working on that data.
static CRITICAL_SECTION criticalSectionAdd;
static CRITICAL_SECTION criticalSectionRemove;

// A list containing info about all run-time instances
static StaticImage* staticImageList[1000];

static inline StaticImage* staticImageList_get(unsigned i)
{
	StaticImage* staticImage = staticImageList[i];
	if (staticImage != NULL && (IsBadWritePtr(staticImage, 1) || staticImage->magic != libcovMagic)) {
		staticImage = NULL;
	}
	return staticImage;
}

//---------------------------------------------------------------------------
// Auto-save thread
//
// We run a single auto-save thread rather than one in each run-time instance
// to prevent the thread code crashing when the image is unloaded (via FreeLibrary).
// We only know of this possibility with the Symbian OS emulator.

// The auto-save thread
static DWORD __stdcall autoSave(void*)
{
	for (;;) {
		Sleep(1000);
		// Granularity is not important, so just hold lock for the duration of the loop
		EnterCriticalSection(&criticalSectionRemove);
		for (unsigned i = sizeofarray(staticImageList); i-- != 0;) {
			StaticImage* staticImage = staticImageList_get(i);
			// If the image was not unloaded
			if (staticImage != NULL) {
				staticImage->covWrite();
			}
		}
		LeaveCriticalSection(&criticalSectionRemove);
	}
}

// Create auto-save thread
static void __stdcall createAutoSave()
{
	static cov_atomic_t once = cov_atomic_initializer;
	if (cov_atomic_tryLock(&once)) {
		const HANDLE handle = CreateThread(NULL, 32 * 1024, autoSave, NULL, 0, NULL);
		SetThreadPriority(handle, THREAD_PRIORITY_BELOW_NORMAL);
	}
}

//---------------------------------------------------------------------------
// Process termination handling
//
// During process termination, the operating system stops all threads,
// including our auto-save thread which might hold locks if they were in
// cov_write when stopped.
// We detect process termination and release the cov_write locks so that we
// can re-call cov_write.

// Events used to determine if the process is terminating
static HANDLE heartBeatQuery;
static HANDLE heartBeatRespond;
static bool isTerminateCertain;

// Every DLL calls this function immediately upon DLL_PROCESS_DETACH
static void processDetach()
{
	static bool isTerminate;
	// If we have not already handled process termination
	if (!isTerminate) {
		// Check for process termination
		isTerminate = isTerminateCertain;
		if (!isTerminate) {
			SetEvent(heartBeatQuery);
			isTerminate = WaitForSingleObject(heartBeatRespond, 10) != WAIT_OBJECT_0;
		}
		// If the process is terminating
		if (isTerminate) {
			// Release resource held by auto-save thread
			//   If the auto-save thread entered criticalSectionRemove when it was killed, we must reset it.
			//   First use DeleteCriticalSection, otherwise upon InitializeCriticalSection, Application Verifier 4.0 complains with:
			//     APPLICATION_VERIFIER_LOCKS_LOCK_ALREADY_INITIALIZED (211) Critical section is already initialized.
			DeleteCriticalSection(&criticalSectionRemove);
			InitializeCriticalSection(&criticalSectionRemove);
			// Release resources held by cov_write functions
			for (unsigned i = sizeofarray(staticImageList); i-- != 0;) {
				StaticImage* staticImage = staticImageList_get(i);
				// If the image was not unloaded
				if (staticImage != NULL) {
					if (staticImage->covWriteLock != NULL) {
						cov_atomic_unlock(staticImage->covWriteLock);
					}
					for (unsigned j = 0; j < fileListSize; j++) {
						FileDescriptor& fileDescriptor = staticImage->fileList[j];
						if (fileDescriptor.lock) {
							CloseHandle(fileDescriptor.handle);
							fileDescriptor.lock = 0;
						}
					}
				}
			}
		}
	}
}

// This thread simply waits on a mutex, and signals another mutex in response.
// If this thread does not respond, the process is terminating.
static DWORD __stdcall heartBeatFunction(void*)
{
	while (
		WaitForSingleObject(heartBeatQuery, INFINITE) == WAIT_OBJECT_0 &&
		SetEvent(heartBeatRespond))
	{
	}
	return 0;
}

//---------------------------------------------------------------------------
// Add and remove

static int __stdcall staticImageAdd(StaticImage* staticImage)
{
	int status = -1;
	staticImage->threadId = GetCurrentThreadId();
	EnterCriticalSection(&criticalSectionAdd);
	for (unsigned i = sizeofarray(staticImageList); i-- != 0;) {
		if (staticImageList[i] == NULL) {
			staticImageList[i] = staticImage;
			status = 0;
			break;
		}
	}
	LeaveCriticalSection(&criticalSectionAdd);
	return status;
}

static void __stdcall staticImageRemove(StaticImage* staticImage)
{
	processDetach();
	EnterCriticalSection(&criticalSectionRemove);
	for (unsigned i = sizeofarray(staticImageList); i-- != 0;) {
		if (staticImageList[i] == staticImage) {
			staticImageList[i] = NULL;
			break;
		}
	}
	LeaveCriticalSection(&criticalSectionRemove);
}

//---------------------------------------------------------------------------
// Retrieve interface
// Use __cdecl because the naming convention is the same for all architectures
extern "C"
__declspec(dllexport) const Dynamic* __cdecl init()
{
	static const Dynamic dynamic = {
		createAutoSave,
		staticImageAdd,
		staticImageRemove,
	};
	return &dynamic;
}

//---------------------------------------------------------------------------
// dllMain
extern "C"
int __stdcall dllMain(void*, unsigned why, void*)
{
	if (why == DLL_PROCESS_ATTACH) {
		InitializeCriticalSection(&criticalSectionAdd);
		InitializeCriticalSection(&criticalSectionRemove);
		// Create heart beat thread
		heartBeatQuery = CreateEvent(NULL, false, false, NULL);
		heartBeatRespond = CreateEvent(NULL, false, false, NULL);
		const HANDLE heartBeatHandle = CreateThread(NULL, 4 * 1024, heartBeatFunction, NULL, 0, NULL);
		SetThreadPriority(heartBeatHandle, THREAD_PRIORITY_TIME_CRITICAL);
	}
	if (why == DLL_PROCESS_DETACH) {
		isTerminateCertain = true;
		processDetach();
	}
	if (why == DLL_PROCESS_DETACH || why == DLL_THREAD_DETACH) {
		// Process the atexit parameters
		// This implements atexit EXEs (not DLLs).
		// The call-back causes the run-time to save coverage to file.
		// Normally the list contains at most one entry that is called upon DLL_PROCESS_DETACH.
		// However, if the Symbian OS emulator loads multiple instrumented EXEs, the list may contain multiple entries.
		// The Symbian OS emulator creates a thread for each EXE, and exits that thread when it unloads the EXE.
		// So we store thread IDs and compare them upon DLL_THREAD_DETACH to match the call-back to the same caller thread.
		const unsigned long threadId = GetCurrentThreadId();
		for (unsigned i = sizeofarray(staticImageList); i-- != 0;) {
			StaticImage* staticImage = staticImageList_get(i);
			if (staticImage != NULL && staticImage->exeAtexitParameter != NULL &&
				(why == DLL_PROCESS_DETACH || staticImage->threadId == threadId))
			{
				staticImage->exeAtexitParameter();
				staticImage->exeAtexitParameter = NULL;
			}
		}
	}
	return 1;
}
