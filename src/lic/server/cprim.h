/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + File Name:   cprim.h
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):  all G2 developers
 +
 + Description:  This file defines standard flags for porting within
 +    Gensym.  It should be included initially by every module that contains
 +    platform-dependent code.  Its purpose is to provide flags that take
 +    advantage of commonality across platforms and thereby reduce the
 +    complexity of #ifdefs within the code.  The file is divided into three
 +    sections.
 +      Section I:   This specifies a unique flag for each platform
 +        and serves to document and define the flags. It also documents
 +        predefined flags for the platforms.
 +      Section II:  This identifies and defines system or architecture
 +        standards that cover multiple systems.  Examples include POSIX, SVR4,
 +        mips, and 88open. This section should include only known
 +        industry standards.
 +      Section III: This defines specific flags that are useful for activating
 +        particular features or exposing non-standard commonality.  Flags
 +        in this section should be minimized and carefully justified.
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP
 +
 + External Interface:
 +
 + Dependencies:
 +
 +
 +  Notes:
 +  Modifications:
 +    05/19/05, jv:  Merged cppflags.h into cprim.h.  Intuitively, cppflags.h
 +      comes "first"; however, cppflags.h used to #include cprim.h as the
 +      first thing it did, so I guess that intuition was wrong.  In 8.1r0,
 +      I kind of got rid of cprim.h from the C files, instead having them
 +      all include cppflags.h, knowing that it would include cprim.h, too.
 +      Now I'm combining them, and keeping the order intact: first what used
 +      to be cprim.h, then what used to be cppflags.h
 +
 +    05/19/05, jv: later in the day: decided my intuition was better, and
 +      reversed the order.
 +
 +    11/23/93, mpc: Added/Modified tables in Sections I and II. See Section
 +                   Headers for details.  (refers to cppflags.h)
 +
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef _CPRIM_H
#define _CPRIM_H


#include <stdio.h>
#ifdef __APPLE__
#  include <sys/time.h>
#else
#  include <time.h>
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 %  Section I:  Flags for individual platforms
 %
 %  Description:  This section documents and defines flags for individual
 %    build platforms.  Each platform has four possible sets of flags.
 %      Preferred flag: Flag to be used to refer to the machine.  This flag
 %        identifies the platform uniquely.
 %      Predefined flags: Defined by the compiler.
 %      Derived flags (optional): Defined as combination of other flags.
 %        There should be at most one derived flag, and if present, it should
 %        be the preferred flag.  The code to define derived flags is below.
 %      Explicit flags (optional): To be passed to the compiler explicitly
 %        with the -D option.  This is needed only if predefined and derived
 %        flags fail to provide sufficient distinctions.
 %
 %                         Table of Unique Flags
 %                         ---------------------
 %
 %   Platform   Compiler     Preferred   Predefined         Derived    Explicit
 %   --------   --------     ---------   ----------         -------    --------
 %   alphaosf   cc(osf)      __osf__     __osf__, __alpha,
 %                                       unix
 %
 %   alphavms   cc(DEC)      alphavms    __ALPHA,vms        alphavms
 %
 %   hp9000s700 cc(HP)       __hp9000s700 __hp9000s700,__hpux,
 %                                        hp9000s800,
 %                                        __hp9000s800,unix
 %
 %   hp9000s800 cc(HP)       none*        hp9000s800, __hpux,  hp800*
 %                                       __hp9000s800,unix
 %
 %   hpia64     cc(HP)       HP_IA64     __hpux, __ia64,   HP_IA64, unix
 %                                       __unix
 %
 %   intelnt    cl386(MS)    WIN32       WIN32, _X86_
 %                                       (see ++ below)
 %
 %   linux      gcc(GNU)     linux       linux,unix
 %
 %   mswin      watcom       __WATCOMC__ __WATCOMC__,
 %                                       __WINDOWS__ (with /zw option)
 %              cl(MS)                   _MSDOS, MSDOS (with /Ze option)
 %
 %   rs6000     cc(DEC)      _IBMR2      _IBMR2
 %
 %   sgi        cc           sgi         sgi,mips,SVR3,
 %                                       unix
 %
 %   sparcsol   gcc(cygnus)  sparcsol    sparc,sun,unix,    sparcsol
 %                                       __svr4__
 %
 %   sun4       cc(Sun)      sun4        sparc,sun,unix     sun4
 %   -------------------------------------------------------------------------
 %  ++ nt flags are defined by including "ntwin32.mak" in the makefile.
 %  *  Never used alone. See Notes.
 %
 %  Notes:
 %    Because the preferred flag is unique for a given platform, to change
 %      the preferred flag, one should globally search and replace
 %      the flag in every platform-dependent file.
 %    Observe that all hp9000s800 flags are also defined by the 700. Because
 %      the 700 and 800 #ifdefs are always identical, the "hp9000s800" flag
 %      can be used to include both. If the need ever arises to distinguish
 %      the 800 from the 700 the derived flag "hp800" should be used.
 %
 %  Modifications:
 %    11/23/93, mpc: Fixed table entries in regards to the HP 700 & 800.
 %                   Added derived flag for alphavms and hp800.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 *
 *       #ifdefs to define unique, derived platform identifiers
 *
 *****************************************************************************/

 /********************************************
 *                                           *
 * SET UP MACHINE SPECIFIC PREDEFINED MACROS *
 *                                           *
 ********************************************/

 /*
 * "_IBMR2"     is already defined on IBM AIX unix.
 * "__hpux"     is already defined on HP-UX unix.
 * "sun"        is already defined on the Suns.
 * "sparc"      is already defined on the Sun 4.
 * "vms"        is already defined on VMS systems.
 */


  /* Although __svr4__ is defined only by gcc on the solaris, the redundant
   * sparc definition is added just for safety
   */
#if defined(sparc) && defined(__svr4__) && !defined(sparcsol)
#  define sparcsol
#endif

#if defined(sparc) && !defined(__svr4__)
#  define sun4
#endif

#if defined(__ALPHA) && defined(vms)
#  define alphavms
#endif

#if defined(hp9000s800) && !defined(__hp9000s700)
#  define hp800
#endif

#if defined(__hpux) && defined(__ia64)
#  define HP_IA64
#endif

#ifdef _IBMR2
#  define rs6000
#  define IBM
#  define ibm
#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 %  Section II:  Flags for system or architecture standards.
 %
 %  Description:  This section documents and defines established flags that
 %    cover general classes of platforms.  These flags should be used whenever
 %    possible to determine system-specific calls. Each entry consists of the
 %    following fields.
 %       Flag:  the flag
 %       Type:  predef:  predefined by the compilers
 %              derived: derived from a combination of other flags (the code
 %                for derived flags is below)
 %       Defined for: platforms for which the flag is defined
 %       Comment:  description of flag usage
 %
 %            Table of Flags for Architecture or System Standards
 %            ---------------------------------------------------
 %
 %   Flag    Type     Defined for           Comment
 %   ----    ----     -----------           -------------------------------
 %   __hpux  predef   hp9000 series         All HP-UX machines share many
 %                                          common system conventions
 %
 %   hp9000s800       hp9000s700 and        Used to group the 700 and 800,
 %           predef   hp9000s800            which generally have
 %                                          identical #ifdefs
 %
 %   SVR3    predef   sgi machines          SVR3 is outmoded and to be avoided.
 %           derived  all HP-UX machines    HP-UX is "based on" SVR3;
 %                                          must pass SVVS validation
 %
 %   unix    predef   all unix platforms    Defined explicitly for rs6000
 %                    except rs6000
 %
 %   vms     predef   all vms platforms     Could be used for any VMS platform
 %
 %   WIN32   predef   all nt platforms      Actually defined in ntwin32.mak,
 %                                          which MSoft recommends be included
 %                                          by every makefile
 %
 %   POSIX   derived  all unix platforms    Currently all are POSIX.1 compliant
 %
 %   SVR4    derived  solaris               All are part of Unix International.
 %                                          This symbol is used by the X Cnsrt.
 %
 %   SYSV    derived  SVR3 & SVR4           Established System V conventions,
 %                                          probably fairly solid
 %
 %  Notes:
 %    As a general rule, the most general standard should be used whenever
 %      possible. The exception is 'unix', which should defer to POSIX when
 %      a POSIX standard exists.  In general, POSIX is more general than
 %      SYSV, which is more general than SVR4.
 %    For now we won't use BSD, since many machines provide both SYSV and BSD
 %      compatibility.
 %    Of potential interest are the following.
 %         ------------------------------------------------------------------
 %         ANSI_C  derived  ???                   Applies to system calls only
 %
 %         BSD     derived  sun4                  Freebee Unix
 %
 %         OSF     derived  alphaosf              May include HP and IBM, but
 %                                                not yet
 %
 %         solaris derived  sparcsol & pc's       Solaris runs on many machines
 %
 %         sun     predef   all sun platforms     No longer very useful because
 %                                                SunOS differs from Solaris
 %
 %         sunOS   derived  sun4
 %
 %         -------------------------------------------------------------------
 %
 %  Modifications:
 %    11/23/93, mpc: Added table entries for hp9000s800, and vms.
 %    12/15/93, jh:  Added rs6000 to define "unix".
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 *
 *       #ifdefs to define derived system standards
 *
 *****************************************************************************/

#ifdef __hpux
#  ifndef unix
#    define unix
#  endif
#endif

#ifdef _IBMR2
#  ifndef unix
#    define unix
#  endif
#endif

#if defined(__alpha) && defined(__osf__)
#  ifndef unix
#    define unix
#  endif
#endif

#ifdef __APPLE__
#  ifndef unix
#    define unix
#  endif
#endif



  /* For the time being, all of our Unix ports are POSIX.1 compliant.
   */
#if defined(unix)
#  define POSIX
#endif

  /* SVR4 will probably cover a wider spectrum of Unix platforms as time passes
   */
#if defined(sparcsol)
#  define SVR4
#endif

#if defined(SVR3) || defined(SVR4)
#  define SYSV
#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 %  Section III:  Ad Hoc Flags
 %
 %  Description:  This section documents flags that are useful for exposing
 %    common features among potentially diverse machines.  Extreme care should
 %    be taken to assure that the flags in this section are useful and
 %    intuitive.  The format for entries below is identical to that of
 %    Section II, except that all flags are derived.
 %
 %                  Table of Ad Hoc Flags
 %                  ---------------------
 %
 %   Flag          Defined for              Comment
 %   ----          -----------              -------------------------------
 %   BIG_ENDIAN_P  i386 & alpha platforms   Defined as 1 for big endian machines
 %   MSWINDOWS     Microsoft Windows
 %   XWINDOWS      X11R6 Platforms          All Unix platforms
 %
 %  Notes:
 %    Whenever possible, one should look for system standards that eliminate
 %      the need for ad hoc flags.  Even apparent hardware dependencies can
 %      sometimes be accounted for with calls to functions such as sysconf(),
 %      pathconf() and fpathconf().
 %    One should avoid the temptation to define a new flag for every machine
 %      grouping.  One rule of thumb is that a flag is useful if it separates
 %      all machines into one of two groups (e.g., big endian or little endian).
 %
 %  Modifications:
 %    11/06/95, mpc:  Added flags for XWindows/MSWindows classifications.
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 *
 *       #ifdefs to define ad hoc flags
 *
 *****************************************************************************/

/* Originally copied from ENSURE_NORMAL_UCS_2_BYTE_ORDER in cstreams.c.

   Changed to check hardware identification, not operating system.  It's not
   Windows or Tru64 Unix are little-endian, per se; it's the CPU. Unfortunately,
   PC Unixes (like Linux) seem to use i386 as the symbol, whereas Windows uses
   _X86_, even though we're checking for the same thing.  - jv, 3/10/05
*/
#if defined(i386) || defined(_X86_) || defined(__alpha)
/* || defined(__osf__) || defined(WIN32) || defined(alphavms) */
#  define BIG_ENDIAN_P 0
#else
#  define BIG_ENDIAN_P 1
#endif


#if defined(WIN32)
#  define MSWINDOWS
#else
#  define XWINDOWS
#endif

#if defined(WIN32)
#  if _MSC_VER >= 1400
#    define MSVC8
#  endif
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 %  Section IV:  C Primitives Defines, Macros, Prototypes, etc.
 %
 %  Description:  Here begins what had been the top of cprim.h in 8.1r0 and
 %    earlier.  Most of what comes above this line had been part of cppflags.h.
 %    Reorganized 5/19/05, jv.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef NULL
#  define NULL 0L
#endif

#ifndef TRUE
#  define TRUE 1L
#endif
#ifndef FALSE
#  define FALSE 0L
#endif

#define SUCCESS  0L
#define FAILURE -1L

/*
#define USE_G2_MALLOC_P
*/

/*
#define CHECK_MEMORY
*/

#ifdef CHECK_MEMORY
# ifndef USE_G2_MALLOC_P
#   define USE_G2_MALLOC_P
# endif
#endif

#define TOUPPER(a) ((islower((int) a)) ? toupper((int) a) : ((int) a))
#define TOLOWER(a) ((isupper((int) a)) ? tolower((int) a) : ((int) a))


/* So, we are nice and careful here to only define MAX and MIN if they are not
 * already defined.  However, on HP-UX 10.20 (specifically, nevada), there are
 * include files which are not so circumspect; and if we include those files
 * (specifically, param.h) *after* including this file, we get warnings about
 * macro redefinition.  We should try to remember to include standard system
 * include files first, and then our own include files, unless we have good
 * reason to include them in the other order.  -jv, 1/12/04
 */

#ifndef MAX
#  define MAX(A, B) ((A) > (B) ? (A) : (B))
#endif

#ifndef MIN
#  define MIN(A, B) ((A) > (B) ? (B) : (A))
#endif

/****************************
 *                            *
 * DEFINITIONS FOR G2MALLOC *
 *                            *
 ****************************/

#ifdef USE_G2_MALLOC_P
#  define G2MALLOC(SIZE) g2_malloc(SIZE)
   void *g2_malloc();
#else
#  ifdef IN_G2POINTERS_MODULE
static void *global_malloc_addr;
#    define G2MALLOC(SIZE) (((global_malloc_addr = malloc(SIZE)) == NULL) ? \
  (printf("\nG2Malloc macro Out of memory.\n") , (void *)NULL) : \
  global_malloc_addr)
#  endif
#endif


/* A hack to get around not wanting to depend on Chestnut rtl.  Stolen from
 * rtl/c/object.h, where it is actually dependent on SI_BITS_PER_FIXNUM, which
 * is always 30 the way we use the translator.
  */
#define IMOST_POSITIVE_FIXNUM        ((1L << (30-1)) - 1)



/******************************
 *                              *
 * DEFINITIONS FOR G2POINTERS *
 *                              *
 ******************************/

/*
 * The constant `MAXIMUM_NUMBER_OF_FAST_G2PTRS' gives the number
 * of g2pointers that are going to be kept in arrays.  The rest of
 * the cpointers (which will be mapped into from the g2pointers) will
 * be kept in a binary tree structure.
 */

# define MAXIMUM_NUMBER_OF_FAST_G2PTRS 2048L                /* 8192 is too high */

typedef long int G2pointer;
typedef long Cpointer;




void          g2ext_initialize_g2pointers();
//Gensym-185-HQ-5717416-SF-Memory leaks in the TWNG
void          g2ext_uninitialize_g2pointers();
//Gensym-185-HQ-5717416-SF-Memory leaks in the TWNG
Cpointer  g2ext_map_g2pointer_to_cpointer( /*g2pointer*/ );
G2pointer g2ext_cache_cpointer( /*cpointer*/ );
void          g2ext_decache_g2pointer( /*g2pointer*/ );

Cpointer  g2ext_get_cptr_from_overflow_space( /*g2pointer*/ );
long      g2ext_cpointer_of_g2pointer_is_null( /* g2pointer */ );



   /* mes - 3/11/93: Added the sparcsol to the machines that use fcntl()
    * because FIONBIO is not available for ioctl().  Note that fcntl(),
    * unlike ioctl(), overwrites all flags rather than setting or resetting
    * individual flags.
    * mes & jh - 3/24/93:  Therefore, fcntl (s,F_GETFL,0) is first called to
    * get the flags, then logical or is used to add the needed O_NDELAY.
    */
#if defined(sparcsol)
#  define SET_NON_BLOCKING(s,n) \
          fcntl(s, F_SETFL, O_NDELAY | fcntl (s,F_GETFL,0))
#else
/* jv, 5/19/05 -- the "linux" case used to be "i386", which was intended
 * for an entirely different PC Unix platform.  But it has always applied
 * to Linux, as well, because Linux (on i386, at least) always defines i386.
 * The original "i386" platform is long dead, but we still support Linux,
 * of course.  I'm not sure if this is the best thing to use on Linux, but
 * this is the way it's always been since we started the port.
 */
#  if defined(linux)
#    define SET_NON_BLOCKING(s,n) fcntl(s, F_SETFL, O_NDELAY)
#  else
#    define SET_NON_BLOCKING(s,n) ioctl(s, FIONBIO, (char *) &n)
#  endif
#endif

   /* mes - 3/16/93: The bzero() function is supplied by BSD to clear a block
    * of memory.  The analogous System V function is memset().  The following
    * macro is now provided to distinguish Solaris from other Unix platforms,
    * but consideration should be given to using memset() more widely.
    * Currently this macro is referenced only in process.c.
    *
    * mpc 6-29-93: Win32 does not support bzero() but does provide memset().
    *
    * jv, 5/19/05: Win32 supports ZeroMemory, which is what we use a lot in
    *   the Win32-only files.
    */
#if defined(sparcsol) || defined(WIN32)
#  define MEMZERO(addr,size) memset( ((void *)(addr)), 0, ( (size_t)(size) ) )
#else
#  define MEMZERO(addr,size) bzero( ((char *)(addr)), (size) )
#endif

#if defined(sparcsol)
FILE *g2pvt_fopen (const char *, const char *);
int g2pvt_fclose (FILE *);
#  define GFOPEN g2pvt_fopen
#  define GFCLOSE g2pvt_fclose
#else
#  define GFOPEN fopen
#  define GFCLOSE fclose
#endif


#if defined(WIN32)
#  include <windows.h>
/* On Windows, some of the macros in <ctype.h> expand into code which doesn't
 * work with the MFC version of libc.  We want to be able to link against MFC
 * or non-MFC, without having to recompile.  Defining _CTYPE_DISABLE_MACROS
 * achieves that goal.  -jv, 2/12/04
 */
#  ifndef _CTYPE_DISABLE_MACROS
#    define _CTYPE_DISABLE_MACROS
#  endif
#endif

#define MAX_CMD_LEN 10
#define G2_CMD   0x01
#define TW_CMD   0x02
/* also used by GSI:  */
#define GSI_CMD  0x04
#define ALL_CMD (G2_CMD | TW_CMD | GSI_CMD)
#define UNKNOWN_PRODUCT 0x00

#if defined(_IBMR2) || defined(sgi)
#  define vfork fork
#endif


#define G2PVT_ALWAYS    0
#define G2PVT_DIALOG_START    1
#define G2PVT_DIALOG_CONT     2
#define G2PVT_DIALOG_FINISH   4
#define G2PVT_ERROR    10
#define G2PVT_PROGRESS 20
#define G2PVT_DETAIL   30
#define G2PVT_DUMP     40
#define G2PVT_TOFILE   50
#ifdef __cplusplus
extern "C" void g2pvt_gprintf (short pDebugLevel, char *pFormatString, ...);
#else
extern void g2pvt_gprintf (short pDebugLevel, char *pFormatString, ...);
#endif



#if defined(sparcsol)
/* vsnprintf is defined in /usr/include/stdio.h on flounder and burlington, but
 * only if certain preprocessor symbols are defined. But it doesn't even matter,
 * because we don't get /usr/include/stdio.h, we get stdio.h from
 * /home/gnu-sol/lib/gcc-lib/sparc-sun-solaris2.5/2.7.2/include, where vsnprintf
 * is not defined at all.  It's already scary using vsnprintf, and the fact that
 * it's not in our include files is scarier still, but... oh well.
 */
extern int vsnprintf();
extern int snprintf();

/* same for gethostname, which is defined in unistd.h */
extern int gethostname();
#endif


/*
 * Timeval Operations
 * These were originally defined in cprocess.c
 */

#ifdef POSIX

#define TIMEVAL_ADDMSEC(t, m)                                        \
  do {                                                               \
    time_t sec = (time_t)(m / 1000);                                 \
    (t)->tv_sec += sec;                                              \
    if (((t)->tv_usec += (int)(m - (sec * 1000)) * 1000) > 1000000)  \
      (t)->tv_usec -= 1000000, (t)->tv_sec++;                        \
  } while (0)

#define TIMEVAL_SUB(t1, t2)                      \
  do {                                           \
    if (((t1)->tv_usec -= (t2)->tv_usec) < 0)    \
      (t1)->tv_usec += 1000000, (t1)->tv_sec--;  \
    (t1)->tv_sec -= (t2)->tv_sec;                \
  } while (0)

#define TIMEVAL_GE(a, b)                                           \
  ((a)->tv_sec > (b)->tv_sec ||                                    \
      ((a)->tv_sec == (b)->tv_sec && (a)->tv_usec >= (b)->tv_usec))

#endif /* POSIX */

#endif        /* _CPRIM_H */
