#define dtoa     g2ext_dtoa
#define freedtoa g2ext_freedtoa

#define g_fmt    g2ext_g_fmt

#if defined(i386) || defined(WIN32) || defined(__osf__) || defined(linux)
#  define IEEE_8087
#else
#  define IEEE_MC68k
#endif

#define Long int

#if defined(ALPHA) || defined(__alpha) || defined(__ALPHA)
#  define Llong long
#else
#  if !defined(__GNUC__)
#    define NO_LONG_LONG
#  endif
#endif

#if defined(__hp9000s700) || defined(mips)
#  if !defined(KR_headers)
#    define KR_headers
#  endif
#endif

/* GENSYMCID-907: use pthread mutex for locks */
#if SI_SUPPORT_THREAD
#define MULTIPLE_THREADS
#include <pthread.h>
#endif
