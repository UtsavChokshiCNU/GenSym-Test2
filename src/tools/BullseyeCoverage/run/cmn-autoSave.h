/* $Revision: 10757 $ $Date: 2010-01-13 15:27:04 -0800 (Wed, 13 Jan 2010) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 */

#if Libcov_noAutoSave || Libcov_dynamic
	static int autoSave_create(void)
	{
		return 0;
	}

	static void autoSave_join()
	{
	}
#else
	static pthread_t autoSave_pthread;
	static volatile char autoSave_isRun;
	static int autoSave_pthread_isValid;

	#if !defined(PTHREAD_LINK)
		#define PTHREAD_LINK
	#endif
	static void* PTHREAD_LINK autoSave_thread(void* arg)
	{
		unsigned count = 0;
		arg = arg;
		while (autoSave_isRun) {
			/* Sleep for 1/10th second, practically imperceptible to a human */
			struct timespec rqt;
			rqt.tv_sec = 0;
			rqt.tv_nsec = 100000000;
			if (nanosleep(&rqt, NULL) != 0) {
				break;
			}
			count++;
			if (count == 10 && autoSave_isRun) {
				cov_write();
				count = 0;
			}
		}
		autoSave_pthread_isValid = 0;
		pthread_exit(NULL);
		return NULL;
	}

	static int autoSave_create(void)
	{
		int status = 0;
		const char* p = getenv("COVAUTOSAVE");
		if (p == NULL || p[0] != '0' || p[1] != '\0') {
			autoSave_isRun = 1;
			status = pthread_create(&autoSave_pthread, NULL, autoSave_thread, NULL);
			if (status == 0) {
				autoSave_pthread_isValid = 1;
			} else if (status == ENOSYS) {
				status = 0;
			}
		}
		return status;
	}

	static void autoSave_join(void)
	{
		autoSave_isRun = 0;
		if (autoSave_pthread_isValid) {
			pthread_join(autoSave_pthread, NULL);
		}
	}
#endif
