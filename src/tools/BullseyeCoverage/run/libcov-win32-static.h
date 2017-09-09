/* $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 * Modifying this source file is not recommended because this may interfere with
 * upgrading to a future release. If you need changes, contact Technical Support.
 *
 * This source contains definitions for Windows NT using the static-only configuration
 */

typedef HANDLE pthread_t;

#define PTHREAD_LINK __stdcall

static int pthread_create(pthread_t* thread, const void* attr, void* (__stdcall* start_routine)(void*), void* arg)
{
	int status;
	DWORD unused;
	attr = attr;
	*thread = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)start_routine, arg, 0, &unused);
	if (*thread == NULL) {
		status = (int)GetLastError();
	} else {
		status = 0;
	}
	return status;
}

static void pthread_exit(void* value_ptr)
{
	/* Use TerminateThread rather than ExitThread to avoid notifying DLLs of
	 * thread detach (which might have lead here and would cause a deadlock)
	 */
	TerminateThread(GetCurrentThread(), (DWORD)(DWORD_PTR)value_ptr);
}

static int pthread_join(pthread_t thread, void** value_ptr)
{
	DWORD status;
	int success = GetExitCodeThread(thread, &status);
	if (success && status == STILL_ACTIVE) {
		success = WaitForSingleObject(thread, INFINITE) != WAIT_FAILED;
		if (success) {
			success = GetExitCodeThread(thread, &status);
		}
	}
	if (value_ptr != NULL) {
		DWORD* p = (DWORD*)value_ptr;
		*p = status;
	}
	return success ? 0 : (int)GetLastError();
}
