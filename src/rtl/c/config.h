/*
 * config.h - Definitions specific to target architecture or site
 * Copyright (c) 1991 Chestnut Software, Inc.  All rights reserved.
 */
#ifndef CONFIG_DOT_H
#define CONFIG_DOT_H

#include "common_config.h"
 
/* Basic architectural parameters.  These are unconstrained user choices. */

/* Support output of translator v3+ */
#ifndef SI_SUPPORT_SF
#define SI_SUPPORT_SF 		1
#endif

/* Support output of translator v2 */
#ifndef SI_SUPPORT_MF
#define SI_SUPPORT_MF	       1
#endif

/* The copying GC is faster, but requires more virtual memory. */
#ifndef SI_COPYING_COLLECTOR
#define SI_COPYING_COLLECTOR    1
#endif

/* The old mark and sweep GC required that large objects like arrays
   be accessed indirectly through small headers.  Option now obsolete. */
#ifndef SI_SEPARATE_HEADERS
#define SI_SEPARATE_HEADERS	0
#else
#if SI_SEPARATE_HEADERS
#include "Separate headers are obsolete"
#endif
#endif

/* Cons cells have header words */
#ifndef SI_CONSES_HAVE_HEADERS
#define SI_CONSES_HAVE_HEADERS  0
#endif

/* Is NIL represented as zero or as a pointer? */
#ifndef SI_NIL_IS_ZERO
#define SI_NIL_IS_ZERO		1 
#endif

/* The garbage collector can support incremental heap allocation,
   but not in all configurations.  The default is on, if possible. */
/*
 * Gensym change (jh, 10/26/93) per Rick Harris.  Hardwired
 * SI_SEGMENTED_DYNAMIC_AREA to be 1 so that we get the memory model we need.
 * See corresponding change in uconfig.h
 */
#ifndef SI_SEGMENTED_DYNAMIC_AREA
#define SI_SEGMENTED_DYNAMIC_AREA     1 /* (!SI_COPYING_COLLECTOR) */
#endif /* SI_SEGMENTED_DYNAMIC_AREA */
#define SI_DYNAMICNESS_LABELED   SI_SEGMENTED_DYNAMIC_AREA

/* When global variables are properly protected, mark+sweep collector
   speed and portability are improved by this option. */
/* This option is required for segmented heaps under the copying collector. */
#ifndef SI_VISIT_EXACTLY_ONCE
#define SI_VISIT_EXACTLY_ONCE   1
#endif

#if (SI_SEGMENTED_DYNAMIC_AREA && SI_COPYING_COLLECTOR)
#if !(SI_VISIT_EXACTLY_ONCE && SI_CONSES_HAVE_HEADERS)
/* Note: it is "Impossible configuration for copying collector",
 * but because customers who are willing to provide explicit 
 * memory management and compact list representation might
 * prefer this configuration, we allow it to be 
 * linked with no-collecting applications only as defined in 
 * uconfig.h (with US_ENSURE__GC == 0).
 */
#endif
#endif

/* Don't include CLOS by default */
#ifndef SI_SUPPORT_CLOS
#define SI_SUPPORT_CLOS         0
#endif

/* Perhaps this should really be SI_SUPPORT_MF? */
#if (SI_SUPPORT_CLOS && !SI_SUPPORT_SF)
#include "CLOS is incompatible with version 2"
#endif

/* SI_CLOS_CHECK_INITARGS
 *
 * If true (the default), calls to make-instance and other functions in the
 * object creation and reinitialization protocol perform valid initarg checking
 * as specified.  If false, such checking is not performed.  Setting it to
 * false provides a bit of a performance improvement in make-instance,
 * reinitialize-instance, and change-class, at the cost of reduced error
 * checking. 
 *
 * This flag is only meaningful if SI_SUPPORT_CLOS is true.
 */
#ifndef SI_CLOS_CHECK_INITARGS
#define SI_CLOS_CHECK_INITARGS	1
#endif

/* SI_CLOS_USE_GENERIC_FUNCTION_CACHES
 *
 * If true (the default), generic functions use caches to speed up the
 * effective method lookup.  If false, caches are not used.  This switch is
 * really only useful for debugging the implementation.  A user would probably
 * never want to set this to false.
 *
 * This flag is only meaningful if SI_SUPPORT_CLOS is true.
 */
#ifndef SI_CLOS_USE_GENERIC_FUNCTION_CACHES
#define SI_CLOS_USE_GENERIC_FUNCTION_CACHES	1
#endif

/* SI_CLOS_RECORD_CACHE_STATISTICS
 *
 * If true, generic function cache lookup functions record statistics by
 * incrementing various counters at appropriate points.  This switch is
 * primarily for debugging the cache implementation and tuning an application.
 * Production code should set this to false.
 *
 * The following functions are available to display the statistics:
 *
 * tclos-run:display_cache_statistics &optional stream		[Function]
 *   Print statistics about generic function cache mechanism to stream, which
 *   must be a stream designator.
 *
 * void SI_display_cache_statistics()
 *   Print statistics about generic function cache mechanism to stdout.
 *
 * This flag is only meaningful if SI_SUPPORT_CLOS is true.
 */
#ifndef SI_CLOS_RECORD_CACHE_STATISTICS
#define SI_CLOS_RECORD_CACHE_STATISTICS		1	/* for now */
#endif

/* Use quick cons if possible */
#ifndef SI_INLINED_CONS_ALLOCATOR
#define SI_INLINED_CONS_ALLOCATOR         1
#endif

#if (SI_SUPPORT_CLOS && SI_SEPARATE_HEADERS)
#include "CLOS is incompatible with SI_SEPARATE_HEADERS"
#endif

/* Tagging scheme (number of bits in a pointer tag) */

#ifndef SI_TAG_WIDTH
#define SI_TAG_WIDTH		1
#endif

/* Name changes to avoid conflicts with reserved words; should
   be conditionalized on machine type
 */

/* Putting this here didn't work for gensym for unknown reasons, so
 * for the moment, we are putting it in numbers.c and initfuns.c
 * instead, removing the extern for random from initfuns.h, and
 * putting in an extern for lrandom.
 */

/* #define random			lrandom */

/* Defines to shorten symbol names */

#define initialize_do_external_symbols_iterator init_do_extern_syms
#define Qinitialize_do_external_symbols_iterator Qinit_do_extern_syms

/*
 * Target sizes for areas, in kilobytes
 */

#ifdef Platform_64bit
    #define STATIC_SIZE           	392L
    #define STATIC_INCREMENT	32L

    #define DYNAMIC_SIZE		9216L
    #define DYNAMIC_INCREMENT	128L

    #define LISP_STACK_SIZE		80L

    #ifndef LOCAL_AREA_SIZE          
        #define LOCAL_AREA_SIZE          32768L
        #define LOCAL_AREA_INCREMENT     1024L /* Amount to grow */
    #endif /* !LOCAL_AREA_SIZE */
#else
	//[tam.srogatch][2010-10-01]: It seems that most of these, except LISP_STACK_SIZE, are never used in the rest of code
    #define STATIC_SIZE           	196
    #define STATIC_INCREMENT	16

    #define DYNAMIC_SIZE		4608
    #define DYNAMIC_INCREMENT	64

    #define LISP_STACK_SIZE		40

    #ifndef LOCAL_AREA_SIZE          
        #define LOCAL_AREA_SIZE          8192 * 2  /* 8 * 1024 K */
        #define LOCAL_AREA_INCREMENT     512 /* Amount to grow */
    #endif /* !LOCAL_AREA_SIZE */
#endif

#define EMERGENCY_RESERVE	1


/* RETURN_MULTIPLE_VALUES should be defined iff the translator parameter
   *return-multiple-values* is non-NIL. */
#define RETURN_MULTIPLE_VALUES


/* Given the current representation of initial symbols, one must make
   a tradeoff between the total number of bytes taken by the names of
   all initial symbols (in all packages), and the maximum number of
   initial symbols in any package: the product of these two limits
   must be at most 2^32 (assuming that a long is 32 bits).  By
   default, the limits are both 2^16 = 65536.
   -- Note: index of symbol within package must fit within a short
   (16 bits). -- */

#ifndef LOG_MAX_ISYMBOLS_PER_PACKAGE
#define LOG_MAX_ISYMBOLS_PER_PACKAGE 16 /* or 15 or 14 */
#endif


/* Define IMMEDIATE_BYTE_SPECIFIERS to obtain immediate (non-consed)
   byte specifiers.  Without this, the CL function BYTE will allocate
   dynamic memory.  With immediate byte specifiers, however, the size
   and position components are both restricted to be less than 2^15. */
#define IMMEDIATE_BYTE_SPECIFIERS


/* Define NEW_BIGNUMS to obtain arbitrary-precision integers.  Otherwise,
   integers will be limited to 32 bits. */

#define NEW_BIGNUMS


/***************************************************************************
 *
 * Environment parameters  
 *
 * Conditionalized for different platforms and environments
 * The meaning of flags:

 * for hardware platforms:
 *         i386             - IBM PC and compatibles with Intel i386 chip
 *         sparc            - SUN SPARCstation
 *         vax              - DEC VAX workstations
 *         ... update here
 *
 * for C programming environments:
 *         _INTELC32_       - Intel C 32-bit Code Buildier Kit on IBM PC
 *         __BORLANDC__     - Borland\'s  C and C++
 *         __TURBOC__       - Borland\'s  C and C++
 *         __ZTC__          - Zortech C++ compiler    (in 32-bit mode).
 *         __WATCOMC__      - Watcom  C/C++ compiler  (in 32-bit mode).
 *                            Defines the version of the compiler
 *         _MSC_VER         - Microsoft C.
 *                            Defines the version of the compiler
 *         vms              - VAX VMS OC C compiler
 *         SI_SYSTEM_V      - UNIX System V
 *         MSDOS            - currently used to indicate both IBM PC
 *                              and Microsoft C. will be replaced
 *                              by i386 and _MSC_VER
 *         sun              - Sun OC-3, OC-4  standard C compiler
 *         ultrix           - DEC ultrix C compiler
 **************************************************************************/

/* Define SI_Size_type to be the type of arguments to the malloc() function.
   If include file <sys/stdtypes.h>, _size_type should be the same as
   size_t. */
typedef size_t SI_Size_type;

#if defined(__WATCOMC__)
#define __ZTC__
#endif

#ifdef SI_RUNTIME_INTERNAL /*************************************************/

/* Define HAVE_MEMCPY if the function memcpy() is available.  */

#define HAVE_MEMCPY

/* hp family: different compilers provide different tag-symbols */

#if defined(hp9000s200) || defined(hp9000s300)
#define hp
#endif

#if defined(__hp9000s200) || defined(__hp9000s300)
#define hp
#endif

#if defined(hp9000s400) || defined(hp9000s500)
#define hp
#endif

#if defined(__hp9000s400) || defined(__hp9000s500)
#define hp
#endif

#if defined(hp9000s700) || defined(hp9000s800)
#define hp
#endif

#if defined(__hp9000s700) || defined(__hp9000s800)
#define hp
#endif

#if defined(hpaa) || defined(__hpaa)
#define hp
#endif

/* HP-UX on Itanium doesn't define any of the above, check this. */
#if defined(__hpux)
#define hp
#endif

#if defined(hp)
#define SI_SYSTEM_V
#endif

#if defined(__BORLAND__) || defined(__TURBOC__)
#define SI_TURBOC
#endif

/* Define HAVE_BCOPY if the function bcopy() is
   available. */

#if !defined(vms) && !defined(_INTELC32_) && !defined(__ZTC__) && !defined(hp) && !defined(WIN32) && !defined(sparcsol) && !defined(motorola) && !defined(_nst)
#define HAVE_BCOPY
#endif

/* Define HAVE_MEMMOVE if the function memmove() is available. */

#if defined(vms) || defined(hp) || defined(__ZTC__) || defined(WIN32) || defined (linux) || defined(sparcsol) || defined(motorola) || defined(_nst)
#define HAVE_MEMMOVE
#endif

/* Define HAVE_STRICMP if the functions stricmp() and strnicmp() are
   available and declared in strings.h. */
/* See the defines at the end of this file: stricmp and strnicmp are
   renamed if they get defined locally.  -rh 12jan95 */
#if (defined(sun) && !defined(__SVR4)) || defined(_INTELC32_) || defined(__ZTC__) || defined(WIN32)
#define HAVE_STRICMP
#endif

#if defined(__ZTC__) && !defined(__WATCOMC__)
#define stricmp   strcmpl
#endif

/* Define HAVE_ARC_HYPERBOLIC iff the arc hyperbolic functions asinh,
   acosh, and atanh are available.  If they are, they will probably
   be declared in /usr/include/math.h. */

#ifdef sun
#define HAVE_ARC_HYPERBOLIC
#endif

/* Define HAVE_AINT iff the floating point to integer conversion functions
   aint() and rint() are available.  If they are, they will probably
   be declared in /usr/include/math.h. */

#if defined(sun) && !defined(__SVR4)
#define HAVE_AINT
#endif

/* Define USE_GETTIMEOFDAY in order to use the Berkeley gettimeofday()
   function in preference to the BSD ftime() call within the Lisp
   function get-internal-real-time.  gettimeofday delivers the time in
   microseconds, while ftime only returns milliseconds, but it is not
   available on all Unixes.  See comments in file src/library/gnrnlrlm.c */

#if defined(sgi) || defined(_IBMR2) || defined(sun) || defined(_nst) || defined(__APPLE__)
#define USE_GETTIMEOFDAY
#endif

#if defined(hp) || defined(ultrix) || defined(DGUX) || defined(motorola) || defined (_SEQUENT_)
#define USE_GETTIMEOFDAY
#endif

#if defined(__osf__) || defined(nec)
#define USE_GETTIMEOFDAY
#endif

#if defined(linux)
#define USE_GETTIMEOFDAY
#endif

/* Define USE_GETRUSAGE in order to use the Berkeley getrusage()
   function in preference to the times() call within the Lisp
   function get-internal-run-time.  getrusage delivers the time in
   microseconds, while times only returns 1/60ths of seconds, but it is not
   available on all Unices.  See comments in file misc.c. */

#if defined(sgi) || defined(_IBMR2) || ( defined(sun) && !defined(sparcsol) )
#define USE_GETRUSAGE
#endif

#if defined(hp) || defined(ultrix) || defined(DGUX) || defined (_SEQUENT_)
#define USE_GETRUSAGE
#endif

/* Define USE_CLOCK in order to use the clock() function in preference
   to the times() function within the Lisp function get-internal-run-time.
   clock() delivers run time in microseconds, while clock() delivers it
   in units of 1/60 of a second. */

#if defined(_INTEL32_) || defined(__ZTC__) || defined(WIN32)
#define USE_CLOCK
#endif

#endif /* SI_RUNTIME_INTERNAL **********************************************/

#if defined(_MSC_VER) || defined(__STDC__) && !defined(_IBMR2)
#define SI_HAVE_STDARGS
#define SI_USE_PROTOTYPES 1
#define USE_PROTOTYPES
#endif

/* Most C compilers require declarations like "static type foo();"
   for forward references to static functions; others need to see
   extern instead of static; others prefer no storage class qualifier. */

#if defined(_MSC_VER) || defined(_INTELC32_)
#define FORWARD_STATIC
#else
#define FORWARD_STATIC static
#endif


#if !defined(WIN32)
#if defined(_INTELC32_) || defined(__ZTC__) || defined(_MSC_VER)
#define i386
#endif
#endif /* Win32 */

#if defined(SI_TURBOC)
#define i386
#endif

#if defined(vms) || defined(ultrix) ||  defined(i386) || defined(WIN32) || defined(__osf__) || defined(__x86__) || defined(__x86_64__)
#define RTL_BIG_ENDIAN 0
#else
#define RTL_BIG_ENDIAN 1 /* should be in mparams.h */
#endif


/* Define ALIGNMENT = 2^n-1 = 1, 3, or 7, as required by architecture.
   ALIGNMENT must be 7 on some newer machines, including the sparc and
   probably others, because floating point numbers must be aligned in 
   memory to even 8-byte boundaries.  Run the diagnostic program (with 
   "make diag") to find out what the correct setting should be. */

#ifdef i386
#define ALIGNMENT 1
#else
/* some compilers complain about shrp-defines in comments [D.N.]
   ifdef ????
   define ALIGNMENT 3   - which machines, VAX? 68000?
   else ... endif */
#define ALIGNMENT 7
#endif /* i386 */

/* This should be true if the C compiler and linker are capable of
   producing static initializers that allocate storage that is aligned
   well enough to permit the desired tagging scheme (SI_TAG_WIDTH).
   The following definition will not work in general. */

#ifndef SI_OBJECT_INITIALIZERS_WORK
#define SI_OBJECT_INITIALIZERS_WORK	(SI_TAG_WIDTH < 3)
#endif

/* Floating point characteristics.
 *
 * Currently only one format of floats is supported (corresponding to C
 * doubles) so only one set of these values is needed.
 *
 * SI_FLOAT_MAX		most-positive-double-float
 * SI_FLOAT_NMIN	least-positive-normalized-double-float
 * SI_FLOAT_MIN		least-positive-double-float
 * SI_FLOAT_NEG_MIN	least-negative-double-float
 * SI_FLOAT_NEG_NMIN	least-negative-normalized-double-float
 * SI_FLOAT_NEG_MAX	least-negative-double-float
 *
 * SI_FLOAT_EPSILON	double-float-epsilon
 * SI_FLOAT_NEG_EPSILON	double-float-negative-epsilon
 *
 * SI_FLOAT_RADIX	value for float-radix for double
 * SI_FLOAT_MANT_DIG	value for float-digits for double
 *
 * Note: Rather than making these be defined to actual values, it might be
 * better to define them to be calls to functions whose definitions are
 * conditionalized for the specific architecture.
 */

#ifdef SI_RUNTIME_INTERNAL

/* Define SI_IEEE_FLOATING_POINT if IEEE floating point format used. */

/* Need to add additional cases for which this is true. */
/* Everything else that Gensym has does IEEE. */

#if defined(vax) || defined(DGUX) || defined(motorola)
#define SI_IEEE_FLOATING_POINT	0
#else
#define SI_IEEE_FLOATING_POINT	1
#endif

/* Need to add additional cases for which this is true. */
#if defined(sparc) && !defined(sparcsol)
#define SI_SUPPORT_DENORMS	1
#else
#define SI_SUPPORT_DENORMS	0
#endif

#if SI_IEEE_FLOATING_POINT


#if defined(__ZTC__) || defined(_INTELC32_)
#define SI_FLOAT_MAX		1.7976931348623158E+300
#define SI_FLOAT_NMIN		2.2250738585072015E-300
#else
#define SI_FLOAT_MAX		1.7976931348623158E+308
#define SI_FLOAT_NMIN		2.2250738585072015E-308
#endif

#if SI_SUPPORT_DENORMS
#define SI_FLOAT_MIN		5.0E-324
#else
#define SI_FLOAT_MIN		SI_FLOAT_NMIN
#endif

#define SI_FLOAT_NEG_MIN	-SI_FLOAT_MIN
#define SI_FLOAT_NEG_NMIN	-SI_FLOAT_NMIN
#define SI_FLOAT_NEG_MAX	-SI_FLOAT_MAX

#define SI_FLOAT_EPSILON	1.1102230246251568E-16
#define SI_FLOAT_NEG_EPSILON	5.551115123125784E-17

#define SI_FLOAT_RADIX		2
#define SI_FLOAT_MANT_DIG	53

#else

/*  #ifdef __STDC__ */
/* These numbers are right for lots of platforms that don't define */
/* __STDC__, so we'll make this the default */

#include <float.h>

#define SI_FLOAT_MAX		DBL_MAX
#define SI_FLOAT_NMIN		DBL_MIN
#define SI_FLOAT_MIN		DBL_MIN
#define SI_FLOAT_NEG_MIN	-DBL_MIN
#define SI_FLOAT_NEG_NMIN	-DBL_MIN
#define SI_FLOAT_NEG_MAX	-DBL_MAX

#define SI_FLOAT_EPSILON	DBL_EPSILON
#define SI_FLOAT_NEG_EPSILON	-DBL_EPSILON

#define SI_FLOAT_RADIX		FLT_RADIX
#define SI_FLOAT_MANT_DIG	DBL_MANT_DIG

#endif /* SI_IEEE_FLOATING_POINT */
#endif /* SI_RUNTIME_INTERNAL */


/* Define KLUDGE_DOUBLE_FLOATS if (a) the C type "double" provides the
   only reason that ALIGNMENT must be 7, and (b) you really want nodes
   to be 12 bytes instead of 16, even at the expense of somewhat
   slower floating point arithmetic.  Run the diagnostic program (with 
   "make diag") to find out whether this feature should be enabled. */

/* 
   Per my discussion yesterday with Rick Harris at Chestnut, we are turning off
   the KLUDGE_DOUBLE_FLOATS switch.  By turning this off, we are buying faster
   access to the double inside a double-float at the price of larger double
   floats, 16 bytes vs. 12.  I'm doing this by including within this comment the
   define for it below.  -jra 9/29/93

#if ALIGNMENT >= 7
#define KLUDGE_DOUBLE_FLOATS
#endif

*/

/* The integer type that's the same size as an Object */
typedef Gensym_Long     SI_Long;
typedef Gensym_Ulong    SI_Ulong;
typedef Gensym_Long64   SI_int64;
typedef Gensym_Ulong64  SI_uint64;

#define SI_BITS_PER_BYTE         8   /* CHAR_BIT */

/* For 64-bit machines where we run in 64 bit mode, rather than in 32-bit
   compatibility mode (currently only osf), Object is 64 bits long. But
   we still only use 30 bits for fixnums, sign-extending to fill the remaining
   32 bits. To ensure that the upper 32 bits of a fixnum are never anything
   but all 1's for a negative number or all zeros for a positive number,
   we cast appropriately when boxing an integer with IFIX, or when performing
   integer operations directly on boxed fixnums.
   */

#if defined(__osf__)
#define SI_BITS_PER_OBJECT		64
/* In ISO C, the file we should include here is <stdint.h>, and this file
   should be included on all platforms where it exists and we run in 64-bit
   mode. But this file does not exist on OSF, the only platform where we
   currently run in 64-bit mode. Instead, the integer types are defined in
   inttypes.h, so we include that instead.
   */
#include <inttypes.h>
#define fixnum_arithmetic_type int32_t
#else
#ifdef Platform_64bit
    #define SI_BITS_PER_OBJECT		64   /* CHAR_BIT * sizeof(Object) */
#else
    #define SI_BITS_PER_OBJECT		32   /* CHAR_BIT * sizeof(Object) */
#endif

#define fixnum_arithmetic_type SI_Long
#endif

#ifndef SI_PRECONFIGURED_IMMEDIATES
#define SI_PRECONFIGURED_IMMEDIATES 1
#endif

#if SI_PRECONFIGURED_IMMEDIATES
#ifdef Platform_64bit
    #define SI_PRECONFIGURED_FIXNUM_SIZE 61
#else
    #define SI_PRECONFIGURED_FIXNUM_SIZE 30
#endif
#endif

/* Define INT_MAX if ANSI C include file <limits.h> is unavailable. */
#ifdef SI_RUNTIME_INTERNAL
#ifndef INT_MAX
#if defined(__STDC__)
#include <limits.h>
#else
/* For 32 bit ints.  Other int sizes will need a different value. */
#define INT_MAX		2147483647
#endif /* __STDC__ */
#endif /* ndef INT_MAX */
#endif /* def SI_RUNTIME_INTERNAL */



/*
 * These symbols help guard against accidental mislinking of object
 * files compiled with incompatible configurations.  If you keep this
 * feature enabled, any attempt to link incompatible object files should
 * fail.  Otherwise, a mislinked application will certainly fail in
 * mysterious ways when it is executed.
 */
#ifndef  SI_PREVENT_MISLINKING 
#define SI_PREVENT_MISLINKING	0
#endif


/* 
 * The following defines eliminate the volatile storage class declaration for
 * those compilers that do not support it.  We are still working with Chestnut
 * to find a workaround for this machine so achieve the semantics that volatile
 * would have provided.  -jra & mes 12/21/93
 */

#if (defined(sun) && !defined(sparc)) || defined(DGUX)
#define volatile 
#endif


#ifndef HAVE_STRICMP

#define stricmp RTL_stricmp
#define strnicmp RTL_strnicmp

#endif

#ifdef linux
#define _stricmp strcasecmp
#endif

/* unused flag */
#ifndef SI_SUPPORT_MPS
#define SI_SUPPORT_MPS 0
#endif

#endif /* CONFIG_DOT_H */
