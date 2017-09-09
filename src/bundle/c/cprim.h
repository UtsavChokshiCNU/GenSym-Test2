/* 
 *
 * Module CPRIM.h
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Mark H. David, and Ong, Peng Tsin
 *
 */


 /********************************************
 *                                           *
 * SET UP MACHINE SPECIFIC PREDEFINED MACROS *
 *                                           *
 ********************************************/
 
 /*
 * "AIX"	is already defined on AIX unix.
 * "apollo"	is already defined on the Apollo.
 * "DGUX"	is already defined on DGUX unix.
 * "hpux"       is already defined on hpux unix.
 * "i386"	is already defined in Interactive's UIX OS for 386 machines
 *		as well as AIX on PS/2 and Sequent.
 * "sun"	is already defined on the Suns.
 * "sparc"	is already defined on the Sun 4.
 * "ultrix"	is already defined on the Vax.
 * "vax"	is already defined on the Vax.
 * "vms"	is already defined on VMS systems.
 */

/*
#if defined(hp9000s300) || defined(hp9000s400) || defined(hp9000s700) || defined(hp9000s800) 
#define hpux
#endif
*/

#ifdef _IBMR2
#define rs6000
#define IBM
#define ibm
#ifndef unix
#define unix
#endif
#endif

#ifdef mips
#define decstation
#endif

#ifdef OS2
#ifdef unix
#undef unix
#endif
#endif

#include <stdio.h>

/* To use gfloats on the VAX, a patch has been put in the stdio.h system
 * file for version v3.2-044 of the VAX C compiler. The patch explicitly
 * #defines all flavors of *printf and *scanf to be vaxc$g*printf
 * and vaxc$g*scanf, respectively, when CC$gfloat is defined.  The definitions
 * appear after the extern declarations of the functions. It is easy for
 * this patch to be lost if the build machine is changed.  Once the compiler
 * is upgraded, the patch should no longer be necessary.
 *   The patched stdio.h file defines GENSYM_GFLOAT_PATCH so that the
 * following error message appears if that file is replaced.
 */
#if defined(vax) && !defined(GENSYM_GFLOAT_PATCH)
#include " -- Error: The stdio.h patch has been lost. See note in cprim.h."
#endif

#ifndef NULL
#define NULL 0L
#endif

#if !defined(sun) && !defined(masscomp) && !defined(_SEQUENT_)
#include <stdlib.h>
#endif

#include <string.h>
#include <ctype.h>
#include <errno.h>

#if !defined(VMS) && !defined(NeXT) && !defined(_CX_UX)
#include <malloc.h>
#endif

#ifndef TRUE
#define TRUE 1L
#endif
#ifndef FALSE
#define FALSE 0L
#endif


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

#ifndef MAX
#define MAX(A, B) ((A) > (B) ? (A) : (B))
#endif

#ifndef MIN
#define MIN(A, B) ((A) > (B) ? (B) : (A))
#endif

/****************************
 *			    *
 * DEFINITIONS FOR G2MALLOC *
 *			    *
 ****************************/

#ifdef USE_G2_MALLOC_P
#  include <signal.h>
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


/******************************
 *			      *
 * DEFINITIONS FOR G2POINTERS *
 *			      *
 ******************************/

/*
 * The constant `MAXIMUM_NUMBER_OF_FAST_G2PTRS' gives the number
 * of g2pointers that are going to be kept in arrays.  The rest of
 * the cpointers (which will be mapped into from the g2pointers) will
 * be kept in a binary tree structure.
 */

# define MAXIMUM_NUMBER_OF_FAST_G2PTRS 2048L		/* 8192 is too high */

typedef long int G2pointer;
typedef long Cpointer;




void	  g2ext_initialize_g2pointers();
Cpointer  g2ext_map_g2pointer_to_cpointer( /*g2pointer*/ );
G2pointer g2ext_cache_cpointer( /*cpointer*/ );
void	  g2ext_decache_g2pointer( /*g2pointer*/ );

Cpointer  g2ext_get_cptr_from_overflow_space( /*g2pointer*/ );


/*
 * g2ext_g2pointer_to_cpointer_array[]
 */
#ifndef IN_G2POINTERS_MODULE
  extern Cpointer g2ext_g2pointer_to_cpointer_array[MAXIMUM_NUMBER_OF_FAST_G2PTRS];
#endif


#define MAP_G2POINTER(G2PTR) \
	( \
	(G2PTR < MAXIMUM_NUMBER_OF_FAST_G2PTRS) \
	? g2ext_g2pointer_to_cpointer_array[G2PTR] \
	: g2ext_get_cptr_from_overflow_space((G2pointer) G2PTR) \
	)



#ifdef _FTX /* stratus */
#include <sys/filio.h>
#endif

   /* mes - 3/11/93: Added the sparcsol to the machines that use fcntl()
    * because FIONBIO is not available for ioctl().  Note that fcntl(),
    * unlike ioctl(), overwrites all flags rather than setting or resetting
    * individual flags.
    * mes & jh - 3/24/93:  Therefore, fcntl (s,F_GETFL,0) is first called to
    * get the flags, then logical or is used to add the needed O_NDELAY.
    *
    * mes - 4/5/93: Added the motorola as yet another SVR4 architecture that
    * does not provide FIONBIO.
    *
    * mes - 6/8/93: Added the nec as another.
    */
#if defined(sparcsol) || defined(motorola) || defined(nec)
#define SET_NON_BLOCKING(s,n) \
          fcntl(s, F_SETFL, O_NDELAY | fcntl (s,F_GETFL,0))
#else
#  if defined(i386) && !defined(__WATCOMC__)
#  define SET_NON_BLOCKING(s,n) fcntl(s, F_SETFL, O_NDELAY)
#  else
#  define SET_NON_BLOCKING(s,n) ioctl(s, FIONBIO, (char *) &n)
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
    */
#if defined(sparcsol) || defined(WIN32) || defined(_nst)
#define MEMZERO(addr,size) memset( ((void *)(addr)), 0, ( (size_t)(size) ) )
#else
#define MEMZERO(addr,size) bzero( ((char *)(addr)), (size) )
#endif



#ifdef _IBMR2
#include <sys/select.h> /* only needed on this platform */
#endif

#if defined(WIN32)
#include <windows.h>
#endif

  /* Used in g2ext_print_command_line_usage(). */
#define MAX_CMD_LEN 10
#define G2_CMD   0x01
#define TW_CMD   0x02
/* also used by GSI:  */
#define GSI_CMD  0x04
#define ALL_CMD (G2_CMD | TW_CMD | GSI_CMD)

int g2ext_get_gensym_product(/* cmdstr */); /* now also used in msmain.c. */
extern void g2ext_gensym_pause();
extern double g2ext_spawn_command_line_process();

/*
 * jh, 7/8/94.  Added externs to cover "intra-ext" C functions.  These functions
 * previously returned values of type int, and were externed implicitly.  For
 * further details (including what "intra-ext" means) see my note this date in
 * /bt/ab/rtl/c/gensym.h.
 */
extern long g2ext_kill_spawned_command_line(/* double */);
extern long g2ext_g2_gethostname(/* char *, long */);

extern long g2ext_tcpip_close(/* long */);

#if defined(__STDC__)
void g2ext_print_command_line_usage(int cmd);
extern long g2ext_write_string_to_console(char * string);
#else
void g2ext_print_command_line_usage();
extern long g2ext_write_string_to_console();
#endif

#ifdef vms
#define g2ext_unix_cmd_with_string_output g2ext_unix_cmd_with_strout
#define g2ext_unix_cmd_with_string_output_and_timeout_callback g2ext_unix_cmd_with_strouttim
#endif
