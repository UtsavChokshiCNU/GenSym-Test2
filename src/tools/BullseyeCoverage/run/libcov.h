/* $Revision: 10023 $ $Date: 2009-05-29 15:21:58 -0700 (Fri, 29 May 2009) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 */

#if Libcov_interface != 3
	/* If you encounter this error, you need to update your run-time port interface.
	 * See http://www.bullseye.com/help/env_custom.html
	 *
	 * Version 1
	 *   base version
	 *
	 * Version 2
	 *   error_write_screen deleted
	 *   write(2, ...) used to report errors
	 *
	 * Version 3
	 *   All functions must be defined.  The feature test macros are removed.
	 *   Unimplemented functions return a failure code and set errno to ENOSYS.
	 */
	#error Libcov_interface version mismatch
#endif

/* Run-time library probe interface version */
#define Libcov_probe cov_probe_7_11_0
#define Libcov_version 711000u

#if __cplusplus
extern "C" {
#endif

/* Data for one translation unit */
typedef struct CovObject {
	unsigned signature;
	unsigned version;
	struct CovObject* next;
	unsigned char* data;
	unsigned id;
	unsigned data_n;
	unsigned events_written;
	char is_linked;
	char is_found;
	char basename[1];
} CovObject;
#define CovObject_signature 0x5a6b

/* Interface to covgetkernel */
typedef struct {
	unsigned version;
	unsigned arch;
	CovObject* volatile* array;
	unsigned array_size;
} CovKernel;
#define CovKernel_version 1

typedef struct {
	int magic;
	unsigned size;
} cov_dumpHeader;
#define libcovMagic 0x434f5644

#if defined(_WIN32)
	#define Libcov_cdecl __cdecl
#else
	#define Libcov_cdecl
#endif

/* Might already be defined for DLL export */
#if !defined(Export)
#	define Export
#endif

Export int Libcov_cdecl cov_check(void);
Export unsigned Libcov_cdecl cov_eventCount(void);
Export int Libcov_cdecl cov_file(const char* path);
Export int Libcov_cdecl cov_reset(void);
void Libcov_cdecl cov_term(void);
void Libcov_cdecl cov_unlink(void);
Export int Libcov_cdecl cov_write(void);
#if COV_ARRAY
	#if __linux
		extern CovObject* volatile cov_array[];
	#endif
#else
	extern CovObject* volatile cov_list;
#endif

#if __cplusplus
}
#endif
