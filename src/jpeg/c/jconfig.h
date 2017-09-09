/* Hand-edited so that one file works on all G2 platforms */
/* See ext/c/cprim.h for list of all platform-specific defines. */
/* -fmw, 1/2/02; filename referenced above changed, -jv, 10/05/06 */

/* jconfig.h.  Generated automatically by configure.  */
/* jconfig.cfg --- source file edited by configure script */
/* see jconfig.doc for explanations */

#define HAVE_PROTOTYPES 
#define HAVE_UNSIGNED_CHAR 
#define HAVE_UNSIGNED_SHORT 
/* #undef void */
/* #undef const */
#undef CHAR_IS_UNSIGNED
#define HAVE_STDDEF_H 
#define HAVE_STDLIB_H 
#undef NEED_BSD_STRINGS
#undef NEED_SYS_TYPES_H
#undef NEED_FAR_POINTERS
#undef NEED_SHORT_EXTERNAL_NAMES
/* Define this if you get warnings about undefined structures. */
#undef INCOMPLETE_TYPES_BROKEN

#if defined(_IBMR2)             /* RS6000 (rs) */
#define CHAR_IS_UNSIGNED 
#undef HAVE_STDLIB_H
#define NEED_BSD_STRINGS 
#endif

#ifdef WIN32
/* Define "boolean" as unsigned char, not int, per Windows custom */
#ifndef __RPCNDR_H__		/* don't conflict if rpcndr.h already read */
typedef unsigned char boolean;
#endif
#define HAVE_BOOLEAN		/* prevent jmorecfg.h from redefining it */
#endif /* WIN32 */



#ifdef JPEG_INTERNALS

#undef RIGHT_SHIFT_IS_UNSIGNED

/* Basically, we want to define INLINE only when using gcc */
#if !defined(WIN32) && !defined(VMS) && !defined(__osf__) && !defined(__hpux) && !defined(_IBMR2)
#define INLINE __inline__
#undef DEFAULT_MAX_MEM
#undef NO_MKTEMP
#endif

#endif /* JPEG_INTERNALS */
