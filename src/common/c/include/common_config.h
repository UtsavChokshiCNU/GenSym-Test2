#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#if defined(__alpha) || defined(_M_X64) || defined(__x86_64__)
	#define Platform_64bit
#else
	#define Platform_32bit
#endif /* Word length switch */

#if defined(_WIN32) /* Defined for both 32-bit and 64-bit environments */
	#define Platform_Windows
#elif defined(__linux__)
	#define Platform_Linux
#elif defined(__APPLE__) && defined(__MACH__)
	#define Platform_Mac
#elif defined(sun) || defined(__sun)
        #define Platform_Solaris
#endif /* OS switch */

/* see http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures */
#if defined(__alpha) ||  defined(i386) || defined(__i386) || defined(_M_IX86) || defined(__x86__) || defined(_M_X64) || defined(__x86_64__)
	#define Platform_LittleEndian
#else
	#define Platform_BigEndian
#endif

#if defined(Platform_Windows) && defined(Platform_64bit)
	typedef __int64 Gensym_Long;
	typedef unsigned __int64 Gensym_Ulong;
#else
	typedef long Gensym_Long;
	typedef unsigned long Gensym_Ulong;
#endif

#if defined(Platform_Windows)
	typedef __int64 Gensym_Long64;
	typedef unsigned __int64 Gensym_Ulong64;
#else
	typedef long long Gensym_Long64;
	typedef unsigned long long Gensym_Ulong64;
#endif

/* TODO: create a separate header for confident-lenght types and include it here */
typedef long long cltInt64;

#ifdef Platform_Windows
#define XANALYS_API __stdcall 
#else
#define XANALYS_API
#endif

/* Multi-threading support */

#ifndef SI_SUPPORT_THREAD
#define SI_SUPPORT_THREAD 0
#endif

/* Thread-Local Storage on different OS/compilers */
#if SI_SUPPORT_THREAD
#  define ACCESS_ONCE(x)  (*(volatile Object *) &(x))
#  if defined(WIN32)
#    define TLS __declspec(thread) /* Visual C++, Intel C/C++ (Windows) */
#    pragma intrinsic(_ReadWriteBarrier)
#    define barrier()   _ReadWriteBarrier(); MemoryBarrier()
#  else
#    define TLS __thread           /* Sun Studio C/C++, IBM XL C/C++, GNU C & Intel C/C++ (Linux) */
#    define barrier()   __asm__ __volatile__("" : : : "memory")
#  endif
#else
#    define TLS
#    define barrier()
#endif

/* GENSYM-46965: VALUE_CELL_SLOTS is used by SI_Value_cell (runint.h),
   this value should not exceed the potential maximum number of threads in
   user application */

#define VALUE_CELL_SLOTS 9

#endif /* COMMON_CONFIG_H */
