/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      cprim.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Paul V. Lindenfelzer, Brian Matthews, Mark H. David,
 +              Ong, Peng Tsin, and Mike Colena
 +
 + Description: This module contains the c primitives, which include functions
 +              for file io, environment functions, and process control.
 +
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   A function banner may contain the following:
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - String Processing and Debugging Functions
 +      g2ext_puts
 +      g2pvt_debug_level
 +      g_vsnprintf
 +      g_vasprintf
 +      g2pvt_snprintf
 +      g2pvt_gprintf
 +      g2pvt_asprintf
 +   Section:      FUNCTION GROUP - Environment Functions
 +      g2ext_g2_gethostname()                   0000000 Multiply Defined
 +      g2ext_get_user_name()                    0000000 Multiply Defined
 +      g2ext_get_user_homedir()                 0000000 Multiply Defined
 +      g2ext_create_argument_list()             1111111
 +      g2ext_return_argc()                    0000000
 +      g2ext_argv_strlen()                    0000000
 +      g2ext_return_argv()                    0000000
 +      g2ext_environment_variable_strlen()    0000000
 +      g2ext_return_environment_variable()    0000000
 +      g2ext_maybe_wait_for_return_key        0000000
 +      g2ext_heap_command_line()                0000000
 +      g2ext_print_command_line_usage()         0000000
 +
 +   Section:      FUNCTION GROUP - Double-Float Handlers
 +      g2ext_error_in_last_float_op_p()      ???????
 +      g2ext_foreign_partition_float()          0000000 Mixed Ifdefs
 +      g2ext_foreign_reconstruct_float()        0000000 Mixed Ifdefs
 +      g2ext_write_float_from_c()               0000000
 +      g2ext_read_float_from_string()        0000000
 +
 +   Section:      FUNCTION GROUP - Stack/Core Management
 +      g2ext_maximize_stack_size()           0000000 Multiply Defined
 +      g2ext_inhibit_core_dumping()          0000000 Multiply Defined
 +
 +   Section:      FUNCTION GROUP - Miscellaneous
 +      g2ext_exit_from_lisp()                   0000000
 +      g2ext_string_to_uppercase()              0000000
 +      g2ext_get_platform_code()             0000000 Mixed Ifdefs
 +
 +   Section:      FUNCTION GROUP - Sleep Functions
 +      g2ext_max_ready()                     0000000 Mixed Ifdefs
 +      g2ext_gensym_pause()                  0000000 Multiply Defined
 +
 +   Section:      FUNCTION GROUP - UUID Generation Functions
 +      g2ext_uuid_create()                   0000000
 +
 +
 + External Interface:
 +      long     g2ext_g2_gethostname(char *string_buffer, long length)
 +                 Gets the name of the current host.
 +
 +      long     g2ext_get_user_name(char *buff)
 +                 Gets the name of the current user.
 +
 +      long     g2ext_get_user_homedir(char *buff)
 +                 Gets the home directory of the user.
 +
 +      long     g2ext_return_argc(void)
 +                 Returns the value of argc passed to main().
 +
 +      long     g2ext_argv_strlen(int argument_number)
 +                 returns length of the the n'th value stored in
 *                 argument_list.
 +
 +      long     g2ext_return_argv(char *buffer, int argument_number)
 +                 returns the n'th value stored in argument_list.
 +
 +      long     g2ext_environment_variable_strlen(char *name)
 +                 Returns the length of the environment variable with name
 +                 "name".
 +
 +      long     g2ext_return_environment_variable(char *name, char *buffer)
 +                 Copies the value of the environment variable with name
 +                 "name" into "buffer".
 +
 +      void     g2ext_maybe_wait_for_return_key()
 +                 If this is MS Windows, see if we should
 +                 wait for user to press return key.
 +
 +      void     g2ext_check_for_help_request (int argc, char* argv)
 +                   detects "help request" in command line, prints usage
 +                   conventions, and exits(!)
 +
 +      void     g2ext_check_for_logfile (int argc, char* argv)
 +                   (unix only) processes -log option, redirects stdout/err
 +
 +      void     g2ext_heap_command_line (int argc, char* argv)
 +                   1) checks if the user asked for help; otherwise...
 +                   2) stores command-line arguments for use by g2ext_return_argc.
 +
 +      long     g2ext_foreign_partition_float(double this_double,
 +                                       unsigned short *byte_array)
 +                 TBA
 +
 +      double   g2ext_foreign_reconstruct_float(long byte0, long byte1,
 +                                         long byte2, long byte3)
 +                 TBA
 +
 +      void     g2ext_write_float_from_c(char *result_buffer, char *format_string,
 +                                  int precision, double dbl)
 +                 Writes a float into a buffer with the given formatting
 +                 controls
 +
 +      double   g2ext_read_float_from_string(char *string)
 +                 Parses a float from a string buffer
 +
 +      long     g2ext_maximize_stack_size(void)
 +                 sets the stack size to the largest possible value
 +
 +      long     g2ext_inhibit_core_dumping(void)
 +                 In case a signal which cause core dumping gets past our
 +                 signal handlers, we should inhibit core dumping to save
 +                 space on the user's disk.
 +
 +      void     g2ext_exit_from_lisp(long)
 +                 TBA
 +
 +      long     g2ext_get_platform_code(void)
 +                 This function is called from Lisp to initialize the
 +                 variables g2-machine-type and g2-operating-system in
 +                 BOOTSTRAP.
 +
 +      char     *g2ext_string_to_uppercase(char *str)
 +                 Converts characters of a given string to uppercase
 +
 +      long     g2ext_uuid_create(unsigned short *buffer)
 +                 Creates a UUID, puts it into buffer.
 +
 + Dependencies:
 +      This file has no external dependencies.
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   04/01/94, mes:  Rewrote command-line help to provide more flexibility.
 +   03/07/94, mpc:  Added GLOBALS section for module specific typedefs
 +   03/07/94, mpc:  Added GLOBALS section for module specific typedefs
 +                   and variables.
 +   11/23/93, mpc:  Added include for cpp flags and ensured all
 +                   ifdefs conformed to preferred spec.
 +   11/22/93, mpc:  Changed SYSV/BSD platform dependent system calls to
 +                   POSIX standard calls. Removed cprim_toupper() and
 +                   cprim_lower(), replaced with ANSI equivs. Changed
 +                   function banner styles to be less visually straining.
 +   9/28/93, mpc: Changed (__ALPHA) flags in g2ext_get_platform_code() and the
 +                 Double-Float handlers section. It now should be (__ALPHA)
 +                 && (vms) because (__ALPHA) is defined on all alpha platforms.
 +   9/23/93, mpc: Major structural reorganization to improve code legibility
 +                and maintainability.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "cprim.h"
#include "trace.h"

/* Don't know if all UNIX platforms have this. --binghe */
#include <locale.h>

/*--------------- WIN32 -------------*/
#if defined(WIN32)
#  include <windows.h>
#  include <stdlib.h>
#  include <wchar.h>
#endif

/*--------------- UNIX --------------*/
#if defined(unix)

#  include <stdlib.h>
#  include <stdarg.h>
#  include <errno.h>
#  include <string.h>
#  include <ctype.h>
#  include <fcntl.h>

#  if defined(sun4)
#    include <sys/utsname.h>
#  endif

#  include <sys/types.h>

#  include <unistd.h>   /* Needed for vfork(), at least. */

#  include <sys/time.h>

#  if defined(vms) || defined(sgi)
#    include <sys/times.h>
#    include <limits.h>
#    ifndef CLK_TCK
#      define CLK_TCK (60)
#    endif
#  else
#    include <sys/timeb.h>
#  endif

#  include <sys/resource.h> /* Needed for g2ext_maximize_stack_size() */
#  include <pwd.h>
#endif /* unix */

/*--------------- VMS ---------------*/
#ifdef vms

#  include <descrip.h>  /* Needed for g2ext_g2_gethostname() */
#  include <ssdef.h>

#  include <stdio.h>    /* Required header files for VMS getenv and arg list */
#  include <stdlib.h>

#endif /* vms */

#include <assert.h>
#include <limits.h>


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      DEFINES
%
% Description:  Module specific macros defined in this section.
%
% Notes:
%
% Modifications:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define MAX_STRING_FROM_PIPE 255

#define GPRINTF_BUFFER_SIZE 256


  /* Used in g2ext_get_platform_code() */
#define UNKNOWN_PLATFORM_CODE         -1
#define I386_CODE         1
#define DOS_CODE          2
#define AVIION_CODE       3
#define SGI_CODE          4
#define SEQUENT_CODE      5
#define NEXT_CODE         6
#define DECSTATION_CODE   7
#define MASSCOMP_CODE     8
#define HP9000S300_CODE   9
#define HP9000S400_CODE  10
#define HP9000S700_CODE  11
#define HP9000S800_CODE  12
#define RS6000_CODE      13
#define SUN3_CODE        14
#define SUN4_CODE        15
#define SPARCSOL_CODE    16
#define ALPHAVMS_CODE    17
#define MOTOROLA_CODE    18
#define VMS_CODE         19
#define STRATUS_CODE     20
#define HARRIS_CODE      21
#define NEC_CODE         22
#define ALPHAOSF_CODE    23
#define ALPHANT_CODE     24
#define INTELNT_CODE     25
#define NCR_CODE         26
#define WINDOWS95_CODE   27
#define LINUX_CODE       28
#define MAC_CODE         29
#define HPIA64_CODE      30
#define INTELSOL_CODE    31

/* ---- needed in Double Float section --------------- */

#ifdef vms  /* Needed by functions in Double Float section */

#   define VMS_NON_IEEE_PAD 32

  /* The bit fields below are used by g2ext_foreign_reconstruct_float(). They
   *  correspond to floating-point fields for VMS and IEEE floating-point
   *  standards.
   */
                                    /*sign exponent   (hidden bit) significand*/
#   define MAX_POS_VMS_BYTE1 0x7FDF /* 0   11111111101     (1)      1111     */
#   define MIN_NEG_VMS_BYTE1 0x8000 /* 1   00000000000     (1)      0000     */
#   define MAX_NEG_VMS_BYTE1 0xFFDF /* 1   11111111101     (1)      1111     */

#   define ALL_ONES_BYTE_2_3_OR_4   0xFFFF  /* 1111 1111 1111 1111 */
#   define IEEE_EXPONENT_MASK       0x7FF0  /* 0111 1111 1111 0000 */
#   define IEEE_SIGN_MASK           0x8000  /* 1000 0000 0000 0000 */
#   define IEEE_BYTE1_FRACTION_MASK 0x000F  /* 0000 0000 0000 1111 */

/*
 * jh, 3/20/92.  The following constant helps us check bounds for IEEE standard
 * floats.  It was obtained from the constant SI_FLOAT_NMIN in the Chestnut
 * kernel file config.h.  Note that a hypothetical MOST_POSITIVE_GENSYM_FLOAT
 * would be too large to be represented in VMS.
 */
#  define LEAST_POSITIVE_GENSYM_FLOAT 2.2250738585072015E-308
#endif /* vms */


/* --------------------------------------------------- */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %     Does arg_struct serve any purpose?
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

int g2ext_product = UNKNOWN_PRODUCT;

static int max_ready = 0;   /* Used for sleeping functions. */

int g2_argument_count;
char **g2_argument_list;


extern long g2ext_sys_sleep(/* long */);
extern char *g2ext_current_time_no_newline();
extern void g2ext_finish_trace_control_handler();
extern void g2pvt_windows_shutdown();

void g2ext_print_command_line_usage();

#ifdef vms  /* Needed by functions in Double Float section */
    extern double MTH$CVT_D_G(double *this_double);
    extern double MTH$CVT_G_D(double *this_double);
#endif /* vms */

#ifdef WIN32
extern long g2pvt_uuid_create(unsigned short *buffer);
extern void g2pvt_update_taskbar_status_area();
#else
extern char *getenv();
#endif


extern void g2ext_enable_network_io_trace();
extern void g2ext_write_network_io_trace();
char *g2ext_trace_file = 0;

static int error_in_last_float_op = 0;

static short debug_output_level = G2PVT_DETAIL;

#ifdef __APPLE__
extern void g2rtl_initialize_sdefs ();
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - String Processing and Debugging Functions
 %
 % Description:
 %      These functions are used to generate strings, especially for output
 %      for debugging messages.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * int g_vsnprintf(char *s, int size, const char *format, va_list ap)
 *
 *   Description:
 *     Formats a message into a string buffer.  Takes a size, so overrunning the
 *     buffer should not be a problem.  This takes a va_list, which means it
 *     is not very convenient to use directly.  It is only used as a helper
 *     function by the functions which immediately follow it.
 *   Input Arguments:
 *     a string buffer, the size of the buffer, a format string, and a variable
 *     argument list of arguments to be formatted into the buffer per the string
 *   Return value:
 *     the number of characters that the formatted string would take up if it
 *     were fully written, or -1 if the operation could not be completed
 *   Notes:
 *     Not implemented on VMS.  Static to this file.
 *   Modifications:
 *****************************************************************************/
static int g_vsnprintf(char *s, int size, const char *format, va_list ap)
{
  int ret = -1;

#ifndef vms
#  if defined(WIN32)
  ret = _vsnprintf(s, size, format, ap);
#  else
  ret = vsnprintf(s, size, format, ap);
#  endif
  if ((ret >= size) || ((ret == -1) && (s != NULL))) {
    s[size - 1] = '\0'; /* ensure null terminated string in error case */
  }
#endif

  return (int) ret;
}


/*****************************************************************************
 * int g_vasprintf(char **s, const char *format, va_list ap)
 *
 *   Description:
 *     Formats a message into a string, which it creates, and returns the
 *     formatted string (via the first parameter).  It guesses how big a buffer
 *     it needs to use, and will continually try larger buffers as long as
 *     g_vsnprintf returns a value indicating that a larger buffer is needed.
 *     When the function succeeds, or fails in some other way (such as running
 *     out of memory), it returns.  This takes a va_list, which means it is not
 *     very convenient to use directly.  It is only used as a helper function
 *     function by g2pvt_asprintf.
 *   Input Arguments:
 *     a pointer to a string buffer, a format string, and a variable argument
 *     list of arguments to be formatted into the buffer per the string
 *   Return value:
 *     the number of characters written into the buffer, or -1 if the operation
 *     could not be completed
 *   Notes:
 *     Static to this file.  Won't work on VMS, since g_vsnprintf doesn't work
 *     on VMS.
 *   Modifications:
 *****************************************************************************/
static int g_vasprintf(char **s, const char *format, va_list ap)
{
  int len = 128, n;

  if ((*s = (char *)malloc(len)) == NULL) {
    return -1;
  }

  for (;;) {
    n = g_vsnprintf(*s, len, format, ap);
    if (n > -1 && n < len) {
      return (int)n;
    }

    if (n > -1) {
      len = n + 1; /* new length + null byte */
    } else {
      len *= 2; /* hack for glibc 2.0, HP-UX */
    }

    if ((*s = (char *)realloc(*s, len)) == NULL) {
      return -1;
    }
  }
}


/*****************************************************************************
 * int g2pvt_snprintf(char *s, size_t size, const char *format, ...)
 *
 *   Description:
 *     Formats a message into a string buffer.  Takes a size, so overrunning the
 *     buffer should not be a problem.
 *   Input Arguments:
 *     a string buffer, the size of the buffer, a format string, and zero or
 *     more additional arguments to be formatted into the buffer per the string
 *   Return value:
 *     the number of characters that the formatted string would take up if it
 *     were fully written, or -1 if the operation could not be completed
 *   Notes:
 *     Static to this file.  Won't work on VMS, since g_vsnprintf doesn't work
 *     on VMS.
 *   Modifications:
 *****************************************************************************/
int g2pvt_snprintf(char *s, size_t size, const char *format, ...)
{
  va_list ap;
  int n;

  va_start (ap, format);
  n = g_vsnprintf(s, size, format, ap);
  va_end(ap);

  return n;
}




/*****************************************************************************
 * int g2pvt_asprintf(char **s, const char *format, ...)
 *
 *   Description:
 *     Formats a message into a string, which it creates, and returns the
 *     formatted string (via the first parameter).  It guesses how big a buffer
 *     it needs to use, and will continually try larger buffers as long as
 *     g_vsnprintf returns a value indicating that a larger buffer is needed.
 *     When the function succeeds, or fails in some other way (such as running
 *     out of memory), it returns.
 *   Input Arguments:
 *     a pointer to hold the address of a string buffer, a format string, and
 *     zero or more additional arguments to be formatted into the buffer per
 *     the string
 *   Return value:
 *     the number of characters that the formatted string would take up if it
 *     were fully written, or -1 if the operation could not be completed
 *   Notes:
 *     Static to this file.  Won't work on VMS, since g_vsnprintf doesn't work
 *     on VMS.
 *   Modifications:
 *****************************************************************************/
int g2pvt_asprintf(char **s, const char *format, ...)
{
  va_list ap;
  int n;

  va_start (ap, format);
  n = g_vasprintf(s, format, ap);
  va_end(ap);

  return n;
}


/*****************************************************************************
 * void g2ext_puts (char *message)
 *
 *   Description:
 *     Function to print a string to the debug output
 *   Input Arguments:
 *     A string
 *   Return value:
 *     None
 *   Notes:
 *     This is named with g2ext on the theory that it is ok to call it from
 *     Lisp, for the purposes of debugging from Lisp.  It should not be used
 *     for error messages that the user is supposed to see; it is only for
 *     output for developers.
 *   Modifications:  jv, 4/28/06: it used to print to the debug console (only)
 *     on Windows, and stderr on Unix.  Change it to print to both places on
 *     Windows.
 *****************************************************************************/
void g2ext_puts (char *pMessage)
{
#ifdef WIN32
  OutputDebugString(pMessage);
#endif

  fputs(pMessage, stderr);
  /* On Unix, stderr is (supposedly?) always flushed automatically.  On Windows,
   * it apparently does not.  Add this here, and go ahead and do it on Unix,
   * too, just in case.  -jv, 8/01/06
   */
  fflush(stderr);
}


/*****************************************************************************
 * void g2ext_set_debug_level ()
 *
 *   Description:
 *       API function to set value of static variable.
 *   Input Arguments:
 *     the new debugging output level
 *   Return value:
 *     none
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_set_debug_level (short new_level)
{
  debug_output_level = new_level;
}



/*****************************************************************************
 * short g2pvt_debug_level ()
 *
 *   Description:
 *       API function to get value of static variable.
 *   Input Arguments:
 *     none
 *   Return value:
 *     the current debugging output level
 *   Notes:
 *   Modifications:
 *****************************************************************************/
short g2pvt_debug_level ()
{
  return debug_output_level;
}



/*****************************************************************************
 * void g2pvt_gprintf (short pDebugLevel, char *pFormatString, ...)
 *
 *   Description:
 *     Takes a debugging level indicating priority, and if it is high enough
 *     priority, formats a message and sends it to a debugging output.  In the
 *     initial implementation, the only option is to send it to stderr, or the
 *     Windows equivalent, the debugger output window.  In the future, this
 *     could easily be extended to send the messages to various sinks, including
 *     having the destination be dependent on the level: high priority messages
 *     could get a dialog box, middle priority to a logfile, and low priority
 *     ignored, for example.
 *   Input Arguments:
 *     A level (priority), a format string, and zero or more arguments to be
 *     used as arguments for the format string.
 *   Return value:
 *     none
 *   Notes: some probem with varargs on Alpha OSF (Tru64 Unix); just punt on
 *     it for now.  I really only care about Windows and Solaris.  -jv, 2/14/05
 *   Modifications:
 *****************************************************************************/
void g2pvt_gprintf (short pDebugLevel, char *pFormatString, ...)
{
  static char buf[GPRINTF_BUFFER_SIZE];

  buf[0] = '\0';
  if (g2pvt_debug_level() < pDebugLevel) return;
#if defined(WIN32)
  /* format the string */
  g_vsnprintf(buf, GPRINTF_BUFFER_SIZE, pFormatString,
                  (va_list)(&pFormatString+1));
#endif

  g2ext_puts(buf);
}



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Environment Functions
 %
 % Description:
 %      These functions retrieve information about the programs
 %      current executing environment.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(Platform_Solaris)

/*
 * Reserving file descriptors.
 *
 * Workaround added for Fidelity (HQ-4703793).  The problem is that in
 * Solaris stdio.h functions can only open up to 256 file descriptors.
 * This change attempts to avoid this limitation by reserving a
 * configurable number of file descriptors.
 *
 * This change is for Solaris only.  The problem does not seem to
 * exist on other platforms.
 *
 * This is a workaround because there may be a better fix available
 * perhaps using the Solaris open() and dup2() calls.  This change
 * will be replaced when a better fix is available.
 *
 * -- ajs 1/15/2004
 */

/*
 * List of file descriptors that have been reserved by G2.
 */
typedef struct gensym_fd_struct_def {
  FILE *fd;
  struct gensym_fd_struct_def *next;
} gensym_fd_struct;

gensym_fd_struct *available_fd_list = (gensym_fd_struct *) NULL;
int available_fds = 0;
int available_fds_max_size = 0;


/* Minimum number of descriptors to reserve.  This is the number
 * that are reserved if the number is not specified on the commandline */
#define MIN_DESCRIPTORS_TO_RESERVE 2

/* Maximum number of descriptors to reserve.  This is the number
 * that are reserved on startup */
#define MAX_DESCRIPTORS_TO_RESERVE 128

/*
 * Get the number of descriptors to reserve.  This parses the
 * commandline for the -reserve-descriptors option.
 * If the option is not specified this will return the minimum
 * number to reserve.
 */
static int get_descriptors_to_reserve(int argc, char *argv[])
{
  int result = MIN_DESCRIPTORS_TO_RESERVE;
  int i;

  for (i=1; i<argc; i++) {
    if (strcmp(argv[i], "-reserve-descriptors") == 0
        || strcmp(argv[i], "-RESERVE-DESCRIPTORS") ==  0) {

      if (argc == i + 1) {
        fprintf(stderr,
                "Error: Number of descriptors not provided for %s option.\n",
                argv[i]);
        exit(1);
      }

      result = atoi(argv[i + 1]);

      if (errno
          || result < MIN_DESCRIPTORS_TO_RESERVE
          || result > MAX_DESCRIPTORS_TO_RESERVE) {

        fprintf(stderr,
                "Error: Invalid %s option: %s. Value must be an integer\n",
                argv[i],
                argv[i + 1]);
        fprintf(stderr,
                "       in the range of %d to %d\n",
                MIN_DESCRIPTORS_TO_RESERVE,
                MAX_DESCRIPTORS_TO_RESERVE);

        exit(1);
      }
    }
  }

  return result;
}

/*
 * Function which reserves a file descriptor and adds it to the list
 * of reserved file descriptors.
 */
static void reserve_file_descriptor ()
{
  FILE *tmp_fd;
  int last_error;
  gensym_fd_struct *fd_struct;

  tmp_fd = fopen("/dev/null", "r");

  if (tmp_fd == (FILE *)NULL) {
    last_error = errno;
    printf("Error: attempt to reserve file descriptor failed.\n");
    printf("       error returned was %d\n", last_error);
  } else {
    /* printf("Opened /dev/null; fd = %d\n", (int) tmp_fd->_file); */
    fd_struct = (gensym_fd_struct *)malloc(sizeof(gensym_fd_struct));
    fd_struct->fd = tmp_fd;
    fd_struct->next = available_fd_list;
    available_fd_list = fd_struct;
    available_fds++;
  }
}

/*
 * Function that is called to reserve descriptors on startup - called from
 * the main function.
 */
static void reserve_file_descriptors (int argc, char* argv[])
{
  int i;

  available_fds_max_size = get_descriptors_to_reserve(argc, argv);

  for (i=0; i<available_fds_max_size; i++) {
    reserve_file_descriptor();
  }
}

/**
 * Version of fopen which will get file descriptors from
 * the list of reserved descriptors first.
 */
FILE *g2pvt_fopen (const char *filename, const char *mode)
{
  if (available_fd_list != NULL) {
    gensym_fd_struct *fd_struct;

    fd_struct = available_fd_list;
    available_fd_list = fd_struct->next;
    available_fds--;
    fclose(fd_struct->fd);
    free(fd_struct);
  }

  return fopen(filename, mode);
}

/**
 * Version of fclose which will attempt to reserve
 * a descriptor for use next time if the number of
 * descriptors
 */
int g2pvt_fclose (FILE *fd)
{
  int result = fclose(fd);

  if (available_fds < available_fds_max_size) {
    reserve_file_descriptor();
  }

  return result;
}

#endif



/*****************************************************************************
 * long int g2ext_g2_gethostname(char *string_buffer, long length)
 *
 *   Description:
 *     Gets the name of the current host.
 *   Input Arguments:
 *     string_buffer:  Buffer in which to return host name
 *     length:         length of provided buffer
 *   Returns:
 *     string_buffer: null terminated name of host
 *     return value: string length or FAILURE
 *   Notes:
 *     should be called g2_get_hostname() (with extra _ )
 *   Modifications:
 *       7/8/94, jh:  Changed the length argument of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.  Note that all other definitions of this function
 *     use longs.
 *****************************************************************************/
#ifdef vms

long g2ext_g2_gethostname(buffer, length_long)
    char *buffer;
    long length_long;
{
    int   length = (int) length_long;
    struct dsc$descriptor_s desc;
    struct dsc$descriptor_s desc2;
    long  ret;
    short len;
    char  table;
    char  acc_mod;
    char  dst = 0;

    char desc_string[50],desc_string2[50];

    sprintf(desc_string,"SYS$NODE");

    desc.dsc$w_length = strlen(desc_string);
    desc.dsc$a_pointer = &desc_string;
    desc.dsc$b_dtype = DSC$K_DTYPE_T;
    desc.dsc$b_class = DSC$K_CLASS_S;

    desc2.dsc$a_pointer = &desc_string2;
    desc2.dsc$b_dtype = DSC$K_DTYPE_T;
    desc2.dsc$b_class = DSC$K_CLASS_S;
    desc2.dsc$w_length = 49;

    if (lib$sys_trnlog(&desc,&len,&desc2,&table,&acc_mod,&dst) == SS$_NORMAL) {
        /* get rid of final pair of colons if possible */
        desc_string2[(len < 2) ? 0 : (len - 2)] = '\0';
        sprintf(buffer,&desc_string2[1]);
        return (strlen(buffer));
    }
    return (FAILURE);
}
#endif /* vms */

#if defined(WIN32)

long g2ext_g2_gethostname(buffer,length)
    char *buffer;
    long length;
{
    int len = (int)length;

    if (GetComputerName(buffer, &len) ||
        GetEnvironmentVariable("HOSTNAME", buffer, len))
        return (strlen(buffer));

    return (FAILURE);
}
#endif /* WIN32 */

#if defined(unix)

long g2ext_g2_gethostname(string_buffer, length)
    char *string_buffer;
    long length;
{
    long status = gethostname(string_buffer, (int)length);
    return ((status >= 0) ? strlen(string_buffer) : status);
}
#endif   /* unix  */

/*****************************************************************************
 * long g2ext_get_user_name(char *buff)
 *
 *   Description:
 *     Gets the name of the current user.
 *   Input Arguments:
 *     buff:  Buffer in which to return user name
 *   Returns:
 *     buff: null-terminated user name
 *     return value:   SUCCESS or FAILURE
 *   Notes:
 *     This should also have a length parameter, like g2ext_g2_gethostname().
 *     should be called g2_get_user_name().
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *       4/30/96, mes:  Changed this to merge unix and vms.  Unix uses the
 *     POSIX getlogin() to get the name the user logged in with.  OpenVMS 6.2
 *     apparently doesn't define getlogin(), but VMS tech support recommended
 *     the obsolete POSIX cuserid(), which works.
 *       1/22/97, mes:  Changed the Unix call to use cuserid() rather than
 *     getlogin().  The latter does not work under SunOS4.1.x in an emacs
 *     shell.  The Sun man page indicates that the POSIX committee left
 *     out cuserid() because there was unresolvable disagreement about
 *     how to implement it.  I've tested it on all supported Unix platforms
 *     and it works as needed, so we'll forego POSIX compliance for now in this
 *     instance.
 *       6/21/05, yduJ: change to the recommended POSIX getpwuid(geteuid()) on
 *     UNIX systems.  Copied old code to VMS ifdef; if we resurrect VMS, we will
 *     see if the POSIX standard works there, and if so fold VMS back into the
 *     unix ifdef.
 *
 *****************************************************************************/
#if defined(unix)

static char *saved_login_name = 0;

long g2ext_get_user_name(buff)
    char     *buff;
{
    struct passwd *passentry;
    char *login_name;

    if (saved_login_name)
      login_name = saved_login_name;
    else { /* in case pw functions call ypmatch, which is slow */
      passentry = getpwuid(geteuid());
      login_name = passentry->pw_name;
      if (login_name == NULL) {
        buff[0] = '\0';
        return(FAILURE);
      }
      saved_login_name = (char *)malloc(strlen(login_name)+1);
      strcpy(saved_login_name, login_name);
    }

    strcpy(buff, login_name);
    return(SUCCESS);
}
#endif /* unix */

#if defined(vms)
/* Because we no longer have any working VMS system, I could not test the
   getpwuid changes above, so I have copied the old code here in this
   ifdef. --yduJ 6/05*/

static char *saved_login_name = 0;

long g2ext_get_user_name(buff)
    char     *buff;
{
    char *login_name;

    if (saved_login_name)
      login_name = saved_login_name;
    else { /* cuserid seems to end up calling ypmatch, which is slow */
      login_name = cuserid(NULL);
      if (login_name == NULL) {
        buff[0] = '\0';
        return(FAILURE);
      }
      saved_login_name = (char *)malloc(strlen(login_name)+1);
      strcpy(saved_login_name, login_name);
    }

    strcpy(buff, login_name);
    return(SUCCESS);
}


#endif /* vms */

#if defined(WIN32)

long g2ext_get_user_name(buff)
     char     *buff;
{
    char     user_name[128];
    int      buflen = 128;

    if ( GetUserName( user_name, &buflen ) ) {
        strcpy(buff, user_name);
        return(SUCCESS);
    } else {
        return(FAILURE);
    }
}
#endif /* Win32 */

/*****************************************************************************
 * long g2ext_get_user_homedir (char *buff)
 *
 *   Description:
 *     Gets the home directory of the user.
 *   Input Arguments:
 *     buff:  Buffer in which to return user's home directory
 *   Returns:
 *     buff: null-terminated path name for user's home directory
 *     return value: SUCCESS or FAILURE
 *   Notes:
 *     This should also have a length parameter, like g2ext_g2_gethostname().
 *     should be called g2_get_user_homedir()
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *****************************************************************************/
#if defined(unix) || defined(WIN32)

long g2ext_get_user_homedir(buff)
     char     *buff;
{
    char     *user_homedir;

    user_homedir = getenv("HOME");

    if (user_homedir == NULL) {
        return(FAILURE);
    } else {
        strcpy(buff, user_homedir);
        return(SUCCESS);
    }
}
#endif /* unix */

#ifdef vms

long g2ext_get_user_homedir(buff)
     char     *buff;
     /*
      * g2ext_get_user_homedir is currently (12/13/90) not working in VMS -
      * we need to call SYS$TRNLNM on the logical "SYS$LOGIN".
      */
{
 return(FAILURE);
}
#endif

/*****************************************************************************
 * long g2ext_create_argument_list(int argc, char *argv[])
 *
 *   Description:
 *       This makes global, static copies of argc and argv. The data is then
 *     accessed as an abstract data type.
 *   Input Arguments:
 *       argc: number of args passed in
 *       argv: array of args passed
 *   Returns:
 *       return value: 0
 *   Notes:
 *       !! This routine should be the first thing called by main()!
 *       ----
 *       Is there some reason why a global pointer to argv is not used
 *     instead?  After all, the activation record for main() won't vanish.
 *     Is it because XtInitialize() munges argv[] as described in the next
 *     paragraph?
 *       The X toolkit routine XtInitialize destructively parses the argv list
 *     and decrements argc. Any command line arguments dealing with X resources
 *     are deleted from argv and stored in the resource database, and the
 *     value of argc is decremented appropriately.
 *       ----
 *       When copying, is it a good idea to use malloc(); would that conflict
 *     with Chestnut?
 *       ----
 *       The typedef for arg_struct seems completely superfluous.  It appears
 *     to be a useless wrapper.
 *
 *   Modifications:
 *       jh, 9/22/93.  Changed g2ext_create_argument_list() to return a long so that
 *     we may call it as a foreign function instead of in the main file for
 *     G2/TW, since the main file is now automatically generated.
 *****************************************************************************/
long g2ext_create_argument_list(argc, argv)
     int argc;
     char *argv[];
{
    int i;

    g2ext_start_trace_control_handler((0<argc)?argv[0]:0); /* See trace.c */

    g2_argument_list = (char **) malloc(argc * sizeof(char *));

    if (g2_argument_list == NULL)  {
        g2_argument_count = 0;
        printf("\ncprim.c -- Couldn't allocate storage for ");
        printf("managed argument list!\n");
    } else  {
        for (i = 0; i < argc; i++)  {
            if ((g2_argument_list[i]
                 = (char *) malloc((strlen(argv[i])+1) * sizeof(char)))
                == NULL) {
                printf("\ncprim.c -- Out of memory in g2ext_create_argument_list");
                printf("2nd.\n");
                break;
            } else
                strcpy(g2_argument_list[i], argv[i]);
        }
        g2_argument_count = i;
    }
    return 0;
}

/*****************************************************************************
 * long g2ext_return_argc(void)
 *
 *   Description:
 *     Returns the value of argc passed to main().  The value was
 *     stored in the global "argument_count" by g2ext_create_argument_list().
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value: value of argc of main()
 *   Notes:
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *****************************************************************************/
long g2ext_return_argc()
{
    return(g2_argument_count);
}

/*****************************************************************************
 * long g2ext_argv_strlen(int argument_number)
 *
 *   Description:
 *     returns the length of n'th value stored in argument_list.
 *     This is identical to strlen(argv[argument_number]).  If n is
 *     not a valid index into the global "argument_count", this function
 *     returns -1.
 *   Input Arguments:
 *     argument_number: array position of arg whose length is returned
 *   Returns:
 *     return value: a non-negative long represents a valid string length,
 *     -1 reprsents an error.
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2ext_argv_strlen(argument_number)
     long   argument_number;
{
    if (argument_number >= 0 && argument_number < g2_argument_count)  {
        return strlen(g2_argument_list[argument_number]);
    } else {
        return(-1);
    }
}

/*****************************************************************************
 * long g2ext_return_argv(char *buffer, int argument_number)
 *
 *   Description:
 *     returns the n'th value stored in argument_list.
 *     This is identical to argv[argument_number].  If n is
 *     less than the global "argument_count", the corresponding argument
 *     is copied into "buffer".
 *   Input Arguments:
 *     buffer: buffer in which to return specified arg
 *     argument_number: array position of arg to return
 *   Returns:
 *     buffer: the n'th value stored in argument_list
 *     return value: SUCCESS if value was copied, FAILURE otherwise
 *   Notes:
 *   Modifications:
 *       7/8/94, jh:  Changed return type and an argument of this function to
 *     long as part of the project to ensure that foreign functions get the
 *     correct argument and return types.  For further details, see my note
 *     this date in /bt/ab/rtl/c/gensym.h.
 *       12/18/96, jh: Fixed bug waiting to happen wherein g2ext_return_argv()
 *     could have accepted a negative number as an index into the internal
 *     array of command-line arguments.
 *****************************************************************************/
long g2ext_return_argv(buffer, argument_number)
     char *buffer;
     long   argument_number;
{
    if (argument_number >= 0 && argument_number < g2_argument_count)  {
        strcpy(buffer, g2_argument_list[argument_number]);
        return(SUCCESS);
    } else {
        return(FAILURE);
    }
}

/*****************************************************************************
 * long g2ext_environment_variable_strlen(char *name)
 *
 *   Description:
 *     Returns the length of the environment variable with name "name".
 *   Input Arguments:
 *     name: environment variable to lookup
 *   Returns:
 *     return value: a non-negative long represents a valid string length,
 *     -1 reprsents an error.
 *   Notes:
 *   Modifications:
 *****************************************************************************/
long g2ext_environment_variable_strlen(name)
     char *name;
{
    char *temp;

    temp = getenv(name);
    if (temp == NULL)  {
        return(-1);
    } else {
        return strlen(temp);
    }
}

/*****************************************************************************
 * long g2ext_return_environment_variable(char *name, char *buffer)
 *
 *   Description:
 *     Copies the value of the environment variable with name
 *     "name" into "buffer".
 *   Input Arguments:
 *     name: environment variable to lookup
 *     buffer: buffer in which to return the value of the environment variable
 *   Returns:
 *     buffer: value of the environment variable
 *     return value: SUCCESS if value was copied, FAILURE otherwise
 *   Notes:
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *****************************************************************************/
long g2ext_return_environment_variable(name, buffer)
     char *name;
     char *buffer;
{
    char *temp;

    temp = getenv(name);
    if (temp == NULL)  {
        return(FAILURE);
    } else {
        strcpy(buffer, temp);
        return(SUCCESS);
    }
}

/*****************************************************************************
 * void g2ext_set_gensym_product (char *cmdstr)
 *
 *   Description:
 *       This analyzes cmdstr, which may contain a full pathname or renamed
 *     executable, to deduce the product being executed.  If the deduction
 *     fails, ALL_CMD is returned.
 *   Input Arguments:
 *     cmdstr: a string containing the command line command.
 *   Returns:
 *     nothing; a global variable is set
 *   Notes:
 *       The test for GSI is not likely to work because many GSI executables
 *     have a name that does not include "GSI".
 *
 *****************************************************************************/
void g2ext_set_gensym_product (cmdstr)
    char* cmdstr;
{
    int i, product, index;
    char uppercase_cmdstr[MAX_CMD_LEN];
    char *g2ext_string_to_uppercase();

    if (g2ext_product != UNKNOWN_PRODUCT) {
      /* We've already run; no need to run again. */
      return;
    }

     /* Copy the first command-line argument (which should be the command)
      * into uppercase_cmdstr[], be sure that it's null-terminated, then
      * convert it to upper-case so it can be searched for a product name.
      * Note that only the final MAX_CMD_LEN characters of cmdstr are copied.
      */
    i = strlen(cmdstr);
     /* Set index to first position to be copied.*/
    if ( i > MAX_CMD_LEN - 1 )
        index = i - (MAX_CMD_LEN - 1);
    else
        index = 0;

    strncpy (uppercase_cmdstr, &cmdstr[index], MAX_CMD_LEN);
    uppercase_cmdstr[MAX_CMD_LEN-1] = '\0';
    g2ext_string_to_uppercase (uppercase_cmdstr);

     /* Search the command string backwards for product names.  This
      * is the most efficient and most likely way to deduce the product-name
      * correctly.
      *   Begin by setting cmd to ALL_CMD, which causes information for all
      * products to be printed.  If a specific product is found, cmd is
      * reset appropriately and the search terminates.
      */
    index = strlen(uppercase_cmdstr)-2;
    if (index < 0)
        index = 0;
    for (product=ALL_CMD; index>=0 && product==ALL_CMD; index--) {
        if ( strncmp(&uppercase_cmdstr[index],"G2",2) == 0 ) {
            product = G2_CMD;
        } else if ( strncmp(&uppercase_cmdstr[index],"TW",2) == 0 ) {
            product = TW_CMD;
        } else if ( strncmp(&uppercase_cmdstr[index],"GSI",3) == 0 ) {
            product = GSI_CMD;
        }
    }
    g2ext_product = product;
}


/*****************************************************************************
 * void g2ext_maybe_wait_for_return_key()
 *
 *   Description:
 *     If this is MS Windows, see if we should
 *     wait for user to press return key.
 *   Input Arguments:
 *     none
 *   Return value:
 *     none
 *   Notes:
 *   Modifications:
 *****************************************************************************/
typedef void maybe_wait_for_return_key_type ();
maybe_wait_for_return_key_type *g2ext_maybe_wait_for_return_key_fn = 0;

void g2ext_maybe_wait_for_return_key()
{
#if defined(WIN32)
  if (0 != g2ext_maybe_wait_for_return_key_fn)
    (*g2ext_maybe_wait_for_return_key_fn)();
#endif
}

/*****************************************************************************
 * void g2ext_check_for_help_request (int, char *[])
 *
 *   Description: checks to see if the user supplied "-help" as either the first
 *     or last argument on the command line.  We do not recognize -help in the
 *     middle of the line.
 *   Input Arguments:
 *     the command line, as argc and argv
 *   Return value:
 *     none, but might cause the executable to exit altogether
 *   Modifications: jv, 1/19/05: split out of g2ext_heap_command_line
 *   Notes: (from g2ext_heap_command_line)
 *       1/26/98, lgibson: now -help is checked to see if it is the first or
 *        last command, so it can be tacked onto the end of any command line.
 *****************************************************************************/
void g2ext_check_for_help_request (argc, argv)
    int argc;
    char *argv[];
{
  int arg_index = argc - 1;

  if ((arg_index > 0) &&
      ((strcmp(argv[1], "-help") == 0)  /* 0 when identical */
       || (strcmp(argv[1], "-HELP") == 0)
       || (strcmp(argv[arg_index],"-help") == 0)
       || (strcmp(argv[arg_index],"-HELP") == 0)))
    {
      g2ext_print_command_line_usage();
      exit(0);
    }
}


/*****************************************************************************
 * void g2pvt_check_for_logfile(argc, argv)
 * Description:
 *  Look for -log in the commandline and if present and we can open the next arg
 *  as output file, redirect stdout and stderr there.
 *   Input Arguments:
 *     argc: number of args passed in
 *     argv: array of args passed
 *  Return values:  None.  Side effects stdout.
 *****************************************************************************/
#if !defined(WIN32)

FILE *g2pvt_outstream = NULL;

extern long g2ext_write_string_to_console(char*);

void g2ext_check_for_logfile (argc, argv)
    int argc;
    char *argv[];
{
  int i, fd;
  char *filename = NULL;
  char warningbuf[200];

  for (i=1; i<argc; i++) {
    if (strcasecmp(argv[i], "-log") == 0) {  /* 0 when identical */
      if (i+1<argc) {
        filename = argv[i+1];
        break;
      } else {
        g2ext_write_string_to_console("Warning:  -log detected, but no filename given.  Printing to standard output.");
        return;
      }
    }
  }

  if (filename) {
    if (filename[0] == '-') {
      g2pvt_snprintf(warningbuf, 200, "Warning:  -log file initial character is a hyphen (%s).  Possible proper log file name missing.", filename);
      g2ext_write_string_to_console(warningbuf);
    }

    /* Not using freopen because if it fails, stdout gets closed anyway. */
    if ((g2pvt_outstream = fopen(filename, "w")) == NULL) {
      g2pvt_snprintf(warningbuf, 200, "Warning:  Could not open -log file %s.  Printing to standard output.",filename);
      g2ext_write_string_to_console(warningbuf);
      return;
    }
    close(fileno(stdout));
    close(fileno(stderr));
    fd = fileno(g2pvt_outstream);
    dup2(fd, fileno(stdout));
    dup2(fd, fileno(stderr));
  }
}

#endif

/*****************************************************************************
 * void g2ext_heap_command_line (argc, argv)
 *
 *   Description:
 *     Process the command line and do one of the following:
 *      1) Look for a "help" request and if found print help and exit(!).
 *      2) On unix, look for and process -log to redirect standard output.
 *      3) Copy the command line arguments to an internal array for future
 *         access.
 *   Input Arguments:
 *     argc: number of args passed in
 *     argv: array of args passed
 *   Returns:
 *     return value: 0
 *   Notes:
 *       9/24/93,jra:  The function g2ext_heap_command_line is the only one that gets
 *     called from Chestnut's automatically generated main.c file with the
 *     argc and argv arguments.  We don't want the behavior that is
 *     implemented by this function, and we can't otherwise get at argc and
 *     argv yet.  So, I've added a function g2ext_heap_command_line to this file
 *     to usurp Chestnut's and call our function which sets things up with
 *     program arguments.
 *       4nov94, paf!  GSI has its own version of this in gsiannex.c called
 *     gsi_log_command_line().  The GSI version differs only in that it does
 *     not call g2ext_print_command_line_usage() which would get confused by GSI
 *     bridge executable names which often contain the letters 'g2'.  Instead
 *     it prints its own version of the GSI command line options which are a
 *     strict subset of those for G2.
 *       2/5/98, lgibson: IMPORTANT: don't forget to update
 *     gsi_log_command_line() when making any changes here.
 *     I thought about making GSI use this function, but in
 *     order to print help per product, need to know what the
 *     product is, and I don't know how to tell the product at
 *     run-time (and I don't want to change both main() functions
 *     to add another argument to this function).
 *   Modifications:
 *       1/27/94, jh:  A call to g2ext_print_command_line_usage() has been added
 *     to g2ext_heap_command_line(), since the latter is the only function that gets
 *     called from Chestnut's automatically generated main.c file, and we
 *     wish to rely on this automation, and since g2ext_heap_command_line() is the
 *     first function called when an image is launched.
 *****************************************************************************/
void g2ext_heap_command_line (argc, argv)
    int argc;
    char *argv[];
{
    /* make sure global variable g2ext_product is set properly */
    g2ext_set_gensym_product(argv[0]);

    /* If the "-help" command line argument was supplied, we issue a help
     * message and exit.  We do not actually run G2/TW.
     */
    g2ext_check_for_help_request(argc, argv);

#if !defined(WIN32)
    /* Windows handles its log file differently than Unix. */
    g2ext_check_for_logfile(argc, argv);
#endif

    /* This has nothing to do with the command line, but I suppose we want to
     * make sure to do this really early in order to get the best network
     * tracing, and there's not much Gensym C code run until lots of Lisp stuff
     * gets run.  Sticking it in here is the one opportunity to run before Lisp.
     * This code is old; this comment added bv jv, 1/18/05.
     */
    g2ext_trace_file = getenv("G2_NETWORK_TRACE_FILE");
    if (0 != g2ext_trace_file)
      g2ext_enable_network_io_trace();

#if defined(sparcsol)
    reserve_file_descriptors(argc, argv);
#endif

    g2ext_create_argument_list(argc, argv);
}


/*****************************************************************************
 * void g2ext_print_command_line_usage()
 *
 *   Description:
 *       Prints information about the command-line options available to the
 *     product whose name is given in cmdstr.
 *   Input Arguments:
 *     an int describing the product
 *   Returns:
 *     none
 *   Notes:
 *       Option lines are maintained in a static encapsulated array
 *     of structures.  Each structure has two entries: cmd and usage_line.
 *     cmd is the bitwise "or" of relevant products.  The value ALL_CMD
 *     is the bitwise "or" of all products.  Bitwise "and" is used to
 *     determine whether an option is relevant for a given product.
 *
 *       1/27/94, jh:  Note that the "?" is a wildcard character in UNIX, and
 *     so it must be escaped (e.g., g2 \? or g2 '?' or g2 "?").
 *   Modifications:
 *     4/30/94 mes: rewrote this completely.
 *
 *****************************************************************************/
void g2ext_print_command_line_usage()
{
    typedef struct {
        int cmd;
        char* usage_line;
    } usage_entry;

    static usage_entry usage_entries[] =
    {
        { G2_CMD | TW_CMD,
            "-background         <color> | gensym | <path_to_bitmap>" },
#       if defined(WIN32)
        { TW_CMD,                /* -closebox works on G2, but don't document it. */
            "-closebox           {enable | disable | default}" },
        { TW_CMD,                /* -minimize works on G2, but don't document it. */
            "-minimize           {enable | disable}" },
#       endif
        { GSI_CMD,
            "-connect " },
        { GSI_CMD,
            "-connect-class-name            <class_name> " },
        { GSI_CMD,
            "-connect-host                  <host_name> " },
        { GSI_CMD,
            "-connect-initialization-string <string> " },
        { GSI_CMD,
            "-connect-interface-name        <interface_name> " },
        { GSI_CMD,
            "-connect-network               <network> " },
        { GSI_CMD,
            "-connect-port                  <port_number> " },
        { G2_CMD,
            "-default-language   <language> " },
        { G2_CMD,
            "-default-window-style {standard | standard-large | g2-5.x} " },
        { G2_CMD | TW_CMD,
            "-discard-user-settings " },
#       if !defined(WIN32)
        { G2_CMD | TW_CMD,
            "-display            <host>:[:]<displaynum>.<screennum> " },
#       endif
        { G2_CMD,
            "-exit-on-abort " },
        { G2_CMD | TW_CMD,
            "-fonts              <fontdir> " },
        { G2_CMD | TW_CMD,
            "-fullscreen " },
        { G2_CMD,
            "-g2passwdexe        <filename of g2passwd executable> " },
        { G2_CMD | TW_CMD,
            "-geometry           <width>x<height>{+|-}<xoffset>{+|-}<yoffset>" },
        { G2_CMD | TW_CMD,
            "-height             <pixels> " },
        { ALL_CMD,
            "-help " },
#       if !defined(WIN32)
        { G2_CMD | TW_CMD,
            "-icon               <iconname> " },
#       endif
        { G2_CMD,
            "-init               <filename> " },
        { G2_CMD | TW_CMD,
            "-init-string        <string> " },
        { G2_CMD,
            "-kb                 <filename> " },
        { G2_CMD,
            "-kfepindex          <filename> " },
        { G2_CMD,
            "-kfepkojin          <filename> " },
        { G2_CMD,
            "-kfepmain           <filename> " },
        { ALL_CMD,
            "-log                <filename> " },
        { ALL_CMD,
            "  -no-log" },
        { G2_CMD | TW_CMD,
            "-language           {<language>|default} " },
        { G2_CMD | TW_CMD,
            "-cjk-language       {chinese|japanese|korean} " },
        { G2_CMD,
            "-local-window " },
        { G2_CMD | TW_CMD,
            "-mag[nification]    <number from .5 to 2.66 inclusive> " },
        { G2_CMD | TW_CMD,
            "  -x-mag[nification] <number from .5 to 2.66 inclusive> " },
        { G2_CMD | TW_CMD,
            "  -y-mag[nification] <number from .5 to 2.66 inclusive> " },
        { G2_CMD,
            "-module-map         <filename> " },
        { G2_CMD,
            "-module-search-path \"<module-dir-1> [<module-dir-2> ...]\" " },
        { G2_CMD | TW_CMD,
            "-name               <name> " },
        { ALL_CMD,
            "-network            tcpip " },
        { G2_CMD,
            "-netinfo " },
#       if !defined(WIN32)
        { G2_CMD | TW_CMD,
            "-no-backing-store " },
#       endif
        { GSI_CMD,
            "-noconnect " },
        { GSI_CMD,
            "-nolistener " },
        /* The flag to disable the local window is recognized in platforms.lisp,
         * in function (no-local-window-p).  There, as of G2 8.1r0, we recognize
         * either "-no-window" (with a hyphen in the middle) or "-nowindow".
         * Prior to 8.1r0, we only recognized "-nowindow".  Using the one with
         * the hyphen is more consistent with our other command line options,
         * and we now officially "prefer" it; however, of course, we continue
         * to support "-nowindow" for backwards compatibility.  We don't need
         * to still document it in "g2 -help", though.  -jv/mhd, 1/27/05
         */
        /* { G2_CMD,
            "-nowindow " },
            */
#       if defined(WIN32)
        { G2_CMD,
            "-no-tray " },
#       endif
        { G2_CMD,
            "-no-window " },
        { G2_CMD | TW_CMD,
            "-ok                 <filename> " },
        { G2_CMD | TW_CMD,
            "  -v6ok             <filename> " },
        { G2_CMD | TW_CMD,
            "  -v7ok             <filename> " },
        { G2_CMD | TW_CMD,
            "  -v8ok             <filename> " },
        { G2_CMD | TW_CMD,
            "-password           <password> " },
#       if !defined(WIN32)
        { G2_CMD | TW_CMD,
            "-private-colormap " },
#       endif
        { G2_CMD | TW_CMD,
            "-res[olution]       <dots per inch> " },
        { G2_CMD | TW_CMD,
            "  -x-res[olution]   <dots per inch> " },
        { G2_CMD | TW_CMD,
            "  -y-res[olution]   <dots per inch> " },
        { ALL_CMD,
            "-rgn1lmt            <bytes> " },
        { ALL_CMD,
            "-rgn2lmt            <bytes> " },
        { G2_CMD | TW_CMD,
            "-rgn3lmt            <bytes> " },
#       if defined(WIN32)
        { G2_CMD | TW_CMD,
            "-screenlock " },
#       endif
        { G2_CMD | TW_CMD,        /* SSL option */
            "-secure" },
        { G2_CMD,                /* Server certificate (or from env G2_CERT) */
            "-cert               <name>"},
        { TW_CMD,
            "-splashtime         <seconds> " },
        { G2_CMD,
            "-start " },
        { G2_CMD | GSI_CMD,
            "-tcpipexact " },
        { G2_CMD | GSI_CMD,
            "-tcpport            <portnum> " },
        { TW_CMD,
            "-tcptimeout         <milliseconds> " },
        { G2_CMD | TW_CMD,
            "-ui                 {standard | classic} " },
        { G2_CMD | TW_CMD,
            "-user-mode          <mode> " },
        { G2_CMD | TW_CMD,
            "-user-name          <username> " },
        { G2_CMD | TW_CMD,
            "-width              <pixels> " },
        { G2_CMD | TW_CMD,
            "-window             <windowname> " },
        { G2_CMD | TW_CMD,
            "-window-style       {standard | standard-large | g2-5.x} " },
	#ifdef MTG2
	{ G2_CMD,
	    "-threads            <threads> " },
	#endif
        { FALSE, NULL }                 /* explicit terminator */
    };

    usage_entry* usage_ptr;

     /* Iterate through the array of options and print those that match
      * the deduced product.  ALL_CMD matches every product. The array is
      * terminated by an entry whose cmd field is FALSE.
      */
    for (usage_ptr=usage_entries; usage_ptr->cmd; usage_ptr++) {
        if ( g2ext_product & usage_ptr->cmd ) {  /* if option is relevant */
             /* For ALL_CMD, print a prefix, otherwise indent two spaces */
            if (g2ext_product == ALL_CMD)
                switch (usage_ptr->cmd) {
                    case G2_CMD:            printf("(G2 only)     "); break;
                    case TW_CMD:            printf("(TW only)     "); break;
                    case GSI_CMD:           printf("(GSI only)    "); break;
                    case G2_CMD | TW_CMD:   printf("(G2/TW only)  "); break;
                    case G2_CMD | GSI_CMD:  printf("(G2/GSI only) "); break;
                    case TW_CMD | GSI_CMD:  printf("(TW/GSI only) "); break;
                    default:                printf("              "); break;
                }
            else
                printf("  ");

            printf("%s\n", usage_ptr->usage_line);  /* print the option */
        }
    }
#if defined(WIN32)
      if (0 != g2ext_maybe_wait_for_return_key_fn)
        (*g2ext_maybe_wait_for_return_key_fn)();
#endif
}

long g2ext_write_string_to_console_1(char *string, long write_console_p)
{
  char *current_time;
  int chr = 0, last_chr;
  
#ifndef DEBUG
  if (write_console_p) {
#endif
    current_time = g2ext_current_time_no_newline();
    while(0 != (last_chr = chr, chr = *string++)) {
      printf("[%s]   ",current_time); /* three spaces */
      do {
#ifdef WIN32
      /* If this character is ^M, and the next one is ^J, do not output
       * the ^M.  When we output the ^J, aka '\n', ^M^J will get written.
       * Bug HQ-4226302, "log files can look funny on NT" -jv, 10/08/05
       */
        if ((chr != '\r') || (*string != '\n')) putchar(chr);
#else
        putchar(chr);
#endif
        if (chr == '\n') break;
      } while (0 != (last_chr = chr, chr = *string++));
      if (chr == 0) break;
    }
    if (last_chr != 0 && last_chr != '\n') putchar('\n');
    fflush(stdout);
#ifndef DEBUG
  }
#endif
  return 0;
}

long g2ext_write_string_to_console(string)
  char *string;
{
  /* GENSYMCID-1068: "Obtaining more memory" messages are not shown in G2 Server console window and logs. */
  g2ext_write_string_to_console_1(string, 1);
  return 0;
}

/* Used by inline-get-length-of-c-wide-string, defined in lisp/gsi-common.lisp */
/* Used by inline_get_length_of_c_wide_string, defined in rtl/c/gensym.h       */

int g2ext_w16strlen(wstring)
   short *wstring;
{
  int i=0;
  for(;0!=(*wstring);i++,wstring++);
  return i;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Double-Float Handlers
 %
 % Description:  This section contains functions to partition double-floats.
 %
 % Notes:
 %    Bytes in the partitioned float are ICP bytes, which are 16 bits rather
 %      than 8. Partitioning improves efficiency and provides a way to transmit
 %      ICP double-floats without using bignums in the encoding algorithm.
 %    jh, 4/19/93.  G2 now ports to the Alpha, which has the preprocessor
 %      switch "vms", but lacks the preprocessor switch "vax".  We do not
 %      plan to use G_FLOATS on the Alpha.  Even though they are available,
 %      we would like to nudge our customers toward the only standard in
 %      the area, namely IEEE.  Besides, IEEE supports not-a-number and other
 %      exceptional floats, whereas exceptional G_FLOATS signal an error in
 %      the move instruction, and so can't be passed along as can expceptional
 %      floats in UNIX.  The upshot of all this is that we are changing the
 %      "vms" preprocessor switch to "vax" in the float machinery below so
 %      that we may preserve the G_FLOAT transformations on the Vax while
 %      allowing the Alpha to use the preferred IEEE floats.
 %    Re-revised, jh 4/19/93: to differentiate between Vax and VMS
 %      (see above note).
 %    Revised, jh 11/12/91:  G2 on the Vax now uses G_FLOATS, not
 %      D_FLOATS, so the primitive machinery for converting floats to bytes
 %      must be changed.
 %    No Vax floating-point type matches IEEE format exactly.
 %    On the Vax, this file must be compiled with the /G_FLOAT option.
 %      Note that this is not the default, but it is what we use for C
 %      translations compiled on the Vax.  This file must also be linked
 %      with the library vaxcrtlg ahead of vaxcrtl in the search path.
 %      This is typically done with the following logical name assignments:
 %              define lnk$library sys$library:vaxctrlg.olb
 %              define lnk$library_1 sys$library:vaxctrl.olb
 %    MTH$CVT_D_G is a little-known Vax C utility to convert from Vax
 %      floating-point type D to G.  It and its inverse need the following
 %      ANSI-style prototypes to work properly.  These are not needed in 3.0,
 %      but we will keep them around for because they might be useful in the
 %      future.
 %   jh bhyde mes 4/29/93:  When compiled with the /FLOAT=IEEE switch, the
 %      Alpha reverses the bytes in a double float.  When compiled with the
 %      mutually exclusive /G_FLOAT switch, the Alpha does not reverse the
 %      bytes.  We are not sure why the designers of the Alpha C compiler
 %      did things this way,
 %      Additionally, we should consider making use of the CC$gfloat compiler
 %      switch rather than platform-based compiler switches like "vax" or
 %      "__ALPHA" when compiling on platforms built by Digital.  This switch
 %      is pre-defined to be 1 when the CC command line has a /G_FLOAT
 %      qualifier and 0 otherwise.
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %     9/28/93, mpc:  Changed platform identifier __ALPHA below to
 %         (__ALPHA) && (vms). This is because the __ALPHA flag is defined
 %         by both the vms and NT compilers.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * int g2ext_error_in_last_float_op_p(void)
 *
 *   Description:
 *     The function error_in_last_float_op_p() returns 1 if the
 *     most recent call to g2ext_foreign_partition_float() or
 *     g2ext_foreign_reconstruct_float() overflowed due to the discrepancy in
 *     ranges between VMS G-floats and the standard IEEE floats.  A foreign
 *     function interface to this function would allow interested G2 modules
 *     (such as GSI or KB-LOAD) to check the status of float-manipulating
 *     operations and possibly take other action than the default, which is
 *     to coerce the offending float to the IEEE boundaries.
 *   Input Arguments:
 *     none
 *   Returns:
 *     value of global error_in_last_float_op
 *   Notes:
 *     Not currently used.
 *   Modifications:
 *****************************************************************************/
int g2ext_error_in_last_float_op_p()
{
    return error_in_last_float_op;
}






/*****************************************************************************
 * long g2ext_foreign_partition_float(double this_double, unsigned short *byte_array)
 *
 *   Description:
 *     TBA
 *   Input Arguments:
 *     this_double: a double float from the Lisp environment
 *     byte_array: array of unsigned 16-bit integers
 *   Returns:
 *     return value: 0
 *   Notes:
 *     The following VMS-specific expertise was extracted in antiquity
 *       from gw_icp.c in the GSI product.
 *     The first byte of Vax G and D floats needs to be tweaked to match IEEE
 *       format. The following constant is the empirically-determined amount.
 *       This has not changed between G2 2.1 and 3.0 and probably will not
 *       change as long as G_FLOATS and D_FLOATS exist.
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *       3/10/94, jh: Removed alphavms from the "#if defined(vax)" code that
 *     coerces floats smaller than the IEEE minimum to that minimum.  This is
 *     the wrong place to fix the bug where G2 on Alpha VMS crashes upon
 *     receiving a denormalized float.  The right place is
 *     g2ext_foreign_reconstruct_float(), which see.  The corresponding change has
 *     been propagated to the /bt/ab-7sep92/ext/c/ version of this file as
 *     part of G2 3.0 rev6.
 *       3/3/94, jh: Added alphavms to the "#if defined(vax)" code that coerces
 *     floats smaller than the IEEE minimum to that minimum.  Note that the code
 *     that adds VMS_NON_IEEE_PAD is still Vax-specific, as it should be.
 *****************************************************************************/
long g2ext_foreign_partition_float(this_double, byte_array)
     double             this_double;
     unsigned short    *byte_array;
{
    union double_float_union partitioned_float_buffer;
	//[tam.srogatch][2010-09-28]: xanalys fails here, because byte_array==0
       error_in_last_float_op = 0;
       partitioned_float_buffer.float_view = this_double;

#   if !BIG_ENDIAN_P
       byte_array[3] = partitioned_float_buffer.byte_view.byte1;
       byte_array[2] = partitioned_float_buffer.byte_view.byte2;
       byte_array[1] = partitioned_float_buffer.byte_view.byte3;
       byte_array[0] = partitioned_float_buffer.byte_view.byte4;
#   else /* BIG_ENDIAN_P */
       byte_array[0] = partitioned_float_buffer.byte_view.byte1;
       byte_array[1] = partitioned_float_buffer.byte_view.byte2;
       byte_array[2] = partitioned_float_buffer.byte_view.byte3;
       byte_array[3] = partitioned_float_buffer.byte_view.byte4;
#   endif /* not BIG_ENDIAN_P */

    return(1); /* status */
}

long g2ext_foreign_partition_long(this_long, byte_array)
     Gensym_Long64      this_long;
     unsigned short    *byte_array;
{
    union double_float_union partitioned_float_buffer;
    partitioned_float_buffer.long_view = this_long;

#   if !BIG_ENDIAN_P
       byte_array[3] = partitioned_float_buffer.byte_view.byte1;
       byte_array[2] = partitioned_float_buffer.byte_view.byte2;
       byte_array[1] = partitioned_float_buffer.byte_view.byte3;
       byte_array[0] = partitioned_float_buffer.byte_view.byte4;
#   else /* BIG_ENDIAN_P */
       byte_array[0] = partitioned_float_buffer.byte_view.byte1;
       byte_array[1] = partitioned_float_buffer.byte_view.byte2;
       byte_array[2] = partitioned_float_buffer.byte_view.byte3;
       byte_array[3] = partitioned_float_buffer.byte_view.byte4;
#   endif /* not BIG_ENDIAN_P */

    return(1); /* status */
}
/*****************************************************************************
 * double g2ext_foreign_reconstruct_float(long byte0,
 *                                  long byte1,
 *                                  long byte2,
 *                                  long byte3)
 *
 *   Description:
 *     TBA
 *   Input Arguments:
 *     byte0, byte1, byte2, byte3: 16-bit integers
 *   Returns:
 *     return value:
 *   Notes:
 *     original comment: "Argument byte_array is an array of unsigned 16-bit
 *       integers containing sections of the float.  The result is returned
 *       as a double float, which the calling lisp environment must manage."
 *       Presumably this comment is no longer valid.
 *     updated comment (jh, 3/10/94): Arguments byte1, byte2, byte3, and byte4
 *       are longs which should be positive and 16 or fewer bits in width.  The
 *       result is returned as a C double.  Callers of this function in in Lisp
 *       environments must take care to manage the memory involved in "boxing"
 *       this double.
 *     jh, 3/10/94, IEEE note: ANSI/IEEE Std 754-1985 for floating-point numbers
 *       (pp 9-10) states that a denormalized IEEE float has all 0s in its
 *       exponent field and at least one 1 in its fraction field.
 *     jh, 3/10/94, VMS note: In the following block, we replace what we know to
 *       be a denormalized float with the smallest normalized IEEE float of the
 *       proper sign, on Alpha VMS only.  This is because on Alpha VMS, a
 *       denormalized float causes an FPE (floating point exception) simply by
 *       being loaded into a register.  Those non-VMS platforms that signal FPEs
 *       do not do so until after a denormalized float is passed to an arithmetic
 *       operation.  At that point in G2, there is a handler established for FPE.
 *       At that point in a GSI application, the user has control and can
 *       establish a handler.
 *     jh, 3/20/92. The three constants MAX_POS_VMS_BYTE1, MIN_NEG_VMS_BYTE1,
 *       MAX_NEG_VMS_BYTE1 are used to check the range of the bytes
 *       to be reconstructed into a float on the Vax.  If this float would be
 *       out of range for a Vax G-float, the largest possible G-float is
 *       substituted, and error_in_last_float_op is set for the caller to deal
 *       with as it sees fit.
 *     A more complete and platform-independent solution would establish
 *       handlers for FPE throughout the scope of G2 operation.
 *     Note that this code is necessary over and above the vax-specific code
 *       above in this function and in g2ext_foreign_partition_float().  The previous
 *       code was only designed to prevent Vax platforms sending or receiving
 *       out-of-range G-floats and does not address the question of when a
 *       denormalized float is signaled.  Specifically, the code above only
 *       bulletproofs Vaxes against receiving a float that is larger than the
 *       largest G-float, not one that is smaller than the smallest normalized
 *       float, and the code in g2ext_foreign_partition_float stops the Vax platform
 *       alone from trasnmitting demormalized floats.  Other platforms are not
 *       stopped.
 *   Modifications:
 *       3/10/94, jh: Added protection against reading denormalized floats on
 *     those platforms that signal FPE (floating point exception) upon access
 *     rather than during an arithmetic operation.  We don't always have a
 *     handler for FPE outside of arithmetic operations.  Currently, the
 *     platforms affected are Vax VMS and Alpha VMS.  See Notes for further
 *     details.  Also cleaned up byte numbering scheme, so the bytes are
 *     numbered from 1 to 4 consistently, and cleaned up the confusing practice
 *     in the Vax-specific code of referring to fields in
 *     partitioned_float_buffer instead of the argument bytes.  Also made -0.0
 *     immune to VMS_NON_IEEE_PAD, along with +0.0 for the Vax platform.
 *****************************************************************************/
double g2ext_foreign_reconstruct_float(byte1, byte2, byte3, byte4)
    long byte1, byte2, byte3, byte4;
{
    double  this_double;
    union double_float_union partitioned_float_buffer;

#   if !BIG_ENDIAN_P
       partitioned_float_buffer.byte_view.byte1 = byte4;
       partitioned_float_buffer.byte_view.byte2 = byte3;
       partitioned_float_buffer.byte_view.byte3 = byte2;
       partitioned_float_buffer.byte_view.byte4 = byte1;
#   else /* BIG_ENDIAN_P */
       partitioned_float_buffer.byte_view.byte1 = byte1;
       partitioned_float_buffer.byte_view.byte2 = byte2;
       partitioned_float_buffer.byte_view.byte3 = byte3;
       partitioned_float_buffer.byte_view.byte4 = byte4;
#   endif /* not BIG_ENDIAN_P */

#   ifdef vms

         /* Check for denormalized floats in VMS (see IEEE Note above). */
       if ((byte1 & IEEE_EXPONENT_MASK) == 0 &&
           (byte2 || byte3 || byte4 || (byte1 & IEEE_BYTE1_FRACTION_MASK))) {
              /* Denormalized float case (See VMS Note above). */
           error_in_last_float_op = 1;     /* Global */
           if (byte1 & IEEE_SIGN_MASK)
               this_double = - LEAST_POSITIVE_GENSYM_FLOAT;
           else
               this_double = LEAST_POSITIVE_GENSYM_FLOAT;
       } else {
             /* Non-denormalized float case */
           error_in_last_float_op = 0;     /* Global */
           this_double = partitioned_float_buffer.float_view;
       }

#   else /* not vms */

       error_in_last_float_op = 0;
       this_double = partitioned_float_buffer.float_view;

#   endif /* vms */

    return this_double; /* value */
}

Gensym_Long64 g2ext_foreign_reconstruct_long (byte1, byte2, byte3, byte4)
    long byte1, byte2, byte3, byte4;
{
    Gensym_Long64 this_long;
    union double_float_union partitioned_float_buffer;

#   if !BIG_ENDIAN_P
       partitioned_float_buffer.byte_view.byte1 = byte4;
       partitioned_float_buffer.byte_view.byte2 = byte3;
       partitioned_float_buffer.byte_view.byte3 = byte2;
       partitioned_float_buffer.byte_view.byte4 = byte1;
#   else /* BIG_ENDIAN_P */
       partitioned_float_buffer.byte_view.byte1 = byte1;
       partitioned_float_buffer.byte_view.byte2 = byte2;
       partitioned_float_buffer.byte_view.byte3 = byte3;
       partitioned_float_buffer.byte_view.byte4 = byte4;
#   endif /* not BIG_ENDIAN_P */

    this_long = partitioned_float_buffer.long_view;

    return this_long; /* value */
}

/*****************************************************************************
 * void g2ext_write_float_from_c(char *result_buffer,
 *                         char *format_string,
 *                         long precision,
 *                         double dbl)
 *
 *   Description:
 *     Writes a float into a buffer with the given formatting controls
 *   Input Arguments:
 *     result_buffer:
 *     format_string:
 *     precision:
 *     dbl:
 *   Returns:
 *     return value:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_write_float_from_c(result_buffer, format_string, precision, dbl)
     char *result_buffer;
     char *format_string;
     long precision;
     double dbl;
{
#if !defined(WIN32)
    char *p;
    size_t len;
#endif
    sprintf(result_buffer, format_string, precision, dbl);
#if !defined(WIN32)
    /* GENSYMCID-731 -- xu.jingtao@glority.com, 04/16/2012
     * gcc has different printf behaviour against msvc,
     * adjust it to make it same with msvc(G2's style):
     *   To gcc, the exponent always contains at least two digits
     *   (it also contains of a plus or minus sign).
     *   To msvc,the exponent always consists of a plus or minus sign and
     *   a minimum of three digits.
     */
    p = strchr(result_buffer, 'e');
    if (p != NULL) {
        ++p; /* points to char after 'e', it should be '+', '-' or a digit */
        if (*p == '+' ||
            *p == '-')
            ++p; /* '+' or '-' will be overwriten */
        len = strlen(p);
        if (len == 2) { /* It is impossible that len < 2. */
            /* fill lacked prefix zero to make sure that gcc has the same behaviour with msvc. */
            *(p + 3) = '\0';
            *(p + 2) = *(p + 1);
            *(p + 1) = *p;
            *p = '0';
        }
    }
#endif
}

/*****************************************************************************
 * double g2ext_read_float_from_string(char *string)
 *
 *   Description:
 *     Parses a float from a string buffer
 *   Input Arguments:
 *     string:
 *   Returns:
 *     return value:
 *   Notes:
 *     jh 11/20/91:  Added g2ext_read_float_from_string as part of an improvement
 *        in G2's float readers.  Note that the Lisp side does the
 *        preprocessing necessary to assure that sscanf gets something it can
 *        scan.  In particular, the Lisp code does some preflighting to assure
 *        that sscanf never gets a string with a fill pointer and never gets
 *        anything that would over- or underflow.  This preflighting is
 *        necessary because Harbison and Steele, 2nd Edition, p 313 says that
 *        the behavior of non-ANSI-compliant sscanf is unpredictable.
 *
 *   Modifications:
 *     binghe 12/24/2015:  sscanf() may not accept floats in US standard formats
 *        when locales are not en_US or C. For example, in Italian, floats look
 *        like "1,2" instead of "1.2". To solve this program, we have added a new
 *        function g2ext_initialize_locales() at the end of cprim.c and Lisp code
 *        must call it in function LAUNCH-SYSTEM-PROCESS (launch.lisp). However,
 *        there's no literal modification to current function at all.
 *
 *****************************************************************************/
double g2ext_read_float_from_string(string)
    char *string;
{
    double this_double;

    sscanf(string, "%lf", &this_double);
    return this_double;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Stack/Core Management
 %
 % Description:  Functions to manage the stack and core dumps.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long g2ext_inhibit_core_dumping(void)
 *
 *   Description:
 *     In case a signal which cause core dumping gets past our signal
 *     handlers, we should inhibit core dumping to save space on the user's
 *     disk.
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value: SUCCESS or FAILURE
 *   Notes:
 *     This could have the added advantage of not giving unscrupulous
 *       users a core-dumped image to explore for purposes of defeating our
 *       authorization machinery.
 *     The platform #ifdef assumptions below are very questionable.  Are they
 *       up to date?
 *     Is there are reason why g2ext_core_size_resource should be global?  If not,
 *       a single #ifdefed function could be used.
 *     The 'status' variable can be eliminated by putting the setrlimit()
 *       call in the condition of the 'if' statement.
 *   Modifications:
 *       7/8/94, jh:  Changed the return type of this function to long as part
 *     of the project to ensure that foreign functions get the correct argument
 *     and return types.  For further details, see my note this date in
 *     /bt/ab/rtl/c/gensym.h.
 *****************************************************************************/
#if !defined(__hp9000s700) && !defined(vms) && !defined(WIN32)

struct rlimit g2ext_core_size_resource;   /* global? */

long g2ext_inhibit_core_dumping()
{
    int     status;

    /* non-superusers are alllowed to lower a resource (irretrievably) */
    g2ext_core_size_resource.rlim_max = 0;
    g2ext_core_size_resource.rlim_cur = 0;
    status = setrlimit(RLIMIT_CORE, &g2ext_core_size_resource);

    /* See if we were successful. */
    if (status != 0)
        return FAILURE;
    else
        return SUCCESS;
}

#else /* either hp or vms */

long g2ext_inhibit_core_dumping()
{
 return FAILURE;
}
#endif /* neither hp nor vms */

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Miscellaneous
 %
 % Description:
 %      These functions have no logical correlation.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/*****************************************************************************
 * void g2pvt_unix_shutdown(long)
 *
 *   Description:
 *     Clean up the logfile, if any.
 *****************************************************************************/
#if !defined(WIN32)
void g2pvt_unix_shutdown ()
{
  if (g2pvt_outstream != NULL) {
    fclose(g2pvt_outstream);
    g2pvt_outstream = NULL;
  }
}
#endif


/*****************************************************************************
 * void g2ext_exit_from_lisp(long)
 *
 *   Description:
 *     Does a minimal amount of cleanup of C data, and exits the executable.
 *   Input Arguments:
 *     None.
 *   Returns:
 *     None
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_exit_from_lisp (long exit_status)
{
    g2ext_finish_trace_control_handler();
    if (0 != g2ext_trace_file)
      g2ext_write_network_io_trace(g2ext_trace_file);
#ifdef WIN32
    g2pvt_windows_shutdown();
#else
    g2pvt_unix_shutdown();
#endif
    exit((int)exit_status);
}


/*************************************************************************
*  void g2pvt_notify_now_listening ()
*
*  Purpose:
*  Entry:
*  Returns:
*  Comments:
*************************************************************************/
void g2pvt_notify_now_listening ()
{
#ifdef WIN32
  g2pvt_update_taskbar_status_area();
#endif
}


/*****************************************************************************
 * char *g2ext_string_to_uppercase(char *str)
 *
 *   Description:
 *     Converts characters of a given string to uppercase
 *   Input Arguments:
 *     str: string to convert to uppercase
 *   Returns:
 *     str: input string converted to uppercase
 *     return value: pointer to str buffer
 *   Notes:
 *   Modifications:
 *****************************************************************************/
char *g2ext_string_to_uppercase(str)
     char *str;
{
    char *t;

    for (t = str; *t; t++)
        if (islower((int)*t))
            *t = (char) toupper((int)*t);
    return str;
}

/*****************************************************************************
 * void g2ext_verify_operating_system
 *
 *   Description: Gives error messages if the machine information does
 *      not match up with what we thought we were compiling for.  Then,
 *      unless an argument is passed in saying to go ahead and run anyway,
 *      exit the process.  (The default is to exit the process.)
 *   Input Arguments: exit_on_os_conflict_p, which is used to determine
 *      whether or not to exit.
 *   Returns: nothing
 *   Notes:
 *      Cases for other operating systems can be added, but we don't
 *      really know of any other "emulations" that go on besides Solaris
 *      trying to run Sun4 images.
 *   Modifications:
 *****************************************************************************/
void g2ext_verify_operating_system (exit_on_os_conflict_p)
    long exit_on_os_conflict_p;
{
#ifdef sun4
  {
    struct utsname name;
    int status;

    status = uname(&name);
    if (status == -1) {
      fprintf(stderr, "\n\nError: could not obtain machine information.");
    } else if (name.release[0] != '4') {
      fprintf(stderr, "\n\nError: this image is built for version 4 of SunOS.  ");
      fprintf(stderr, "\n       This is version %s.\n", name.release);
    } else {
      return;
    }
    if (exit_on_os_conflict_p) {
      fprintf(stderr, "       Exiting.  If you want to attempt emulation, use the\n");
      fprintf(stderr, "       command-line option '-use-os-emulation'.\n\n");
      fflush(stderr);
      exit(1);
    }
    fprintf(stderr, "       Attempting to run anyway.\n\n");
    fflush(stderr);
  }
#endif
}

/*****************************************************************************
 * long g2ext_get_platform_code()
 *
 *   Description:
 *     This function is called from Lisp to initialize the
 *     variables g2-machine-type and g2-operating-system in BOOTSTRAP.
 *   Input Arguments:
 *     None
 *   Returns:
 *     return value:  Returns a long which describes the platform in which
 *                    this image is running.
 *   Notes:
 *     Previously, this was done in /bt/ab/g2/c/g2main.c, but this code
 *       doesn't belong there, since the translator now generates a main()
 *       file automatically and there is no reason we can't initialize
 *       g2-machine-type and g2-operating-system as we do any other defvars.
 *     Note that some of the C preprocessor switches are "hardwired"
 *       into the C proprocessor (e.g., unix), and we at Gensym supply others
 *       to the C preprocessor via a -D command-line option or its equivalent
 *       (e.g., sparcsol).
 *   Modifications:
 *     8/17/93, jh: As of this date, to add a new platform xxx, #define a
 *         unique code number for xxx_CODE below, then add an #ifdef or
 *         #if clause below, making sure that no other clause gets
 *         triggered.  The association of a given platform with its
 *         operating system happens on the Lisp side, in the module
 *         BOOTSTRAP.  Go to the comments there to finish adding a new
 *         platform.
 *     9/28/93, mpc:  Changed platform identifier __ALPHA below to
 *         (__ALPHA) && (vms). This is because the __ALPHA flag is defined
 *         by both the vms and NT compilers.
 *****************************************************************************/
long g2ext_get_platform_code()
{
    long     platform_code = UNKNOWN_PLATFORM_CODE;

#    ifdef __WATCOMC__
#        error "WATCOMC build no longer supported -jv, 1/18/05"
         platform_code = DOS_CODE;
#    endif

#    ifdef sgi
         platform_code = SGI_CODE;
#    endif

/* 11/15/99: Both the hp9000s700 and 800 machines are now known as 700's */
#    ifdef __hp9000s700
         platform_code = HP9000S700_CODE;
#    endif

#    ifdef HP_IA64
         platform_code = HPIA64_CODE;
#    endif

#    ifdef _IBMR2
         platform_code = RS6000_CODE;
#    endif

#    ifdef sparc
         platform_code = SUN4_CODE;
#    endif

#    ifdef sparcsol
         platform_code = SPARCSOL_CODE;
#    endif

#    if defined(Platform_Solaris) && !defined(sparc)
         platform_code = INTELSOL_CODE;
#    endif

#    ifdef alphavms
         platform_code = ALPHAVMS_CODE;
#    endif

#    ifdef vax
         platform_code = VMS_CODE;
#    endif

#    ifdef __osf__
         platform_code = ALPHAOSF_CODE;
#    endif

#    if defined(WIN32)
             if (GetVersion() < 0x80000000) {
                 /* Windows NT */
                 platform_code = INTELNT_CODE;
             } else if (LOBYTE(LOWORD(GetVersion())) < 4) {
                 /* Win32s on Windows 3.1 */
                 platform_code =  DOS_CODE;
             } else {
                 /* Chicago / Windows95 */
                 platform_code = WINDOWS95_CODE;
             }
#    endif

#    ifdef linux
         platform_code = LINUX_CODE;
#    endif

#    ifdef __APPLE__
         platform_code = MAC_CODE;
         /* Total kludge; see rtl/c/sdefs.c for details.  -jv, 2/3/05 */
         g2rtl_initialize_sdefs();
#    endif

    return platform_code;
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Sleep Functions
 %
 % Description:
 %      These functions pause G2 for a specified period, designed to allow
 %     interruptible sleep on platforms which support it
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * void g2ext_max_ready()
 *
 *   Description:
 *       Indicates number of file descriptors that are ready after sleeping.
 *     Used for debugging only.
 *   Input Arguments:
 *     none
 *   Return value:
 *     none
 *   Notes:
 *   Modifications:
 *****************************************************************************/
void g2ext_max_ready()
{
#   ifdef sun
        printf("\n Max ready from last check %d", max_ready);
        fflush(stdout);
        max_ready = 0;
#   endif
}

/*****************************************************************************
 * void g2ext_gensym_pause (long milliseconds_when_interruptable,
 *                       long milliseconds_when_polling)
 *
 *   Description:
 *       Where supported, this waits for an input event or sleeps for
 *     milliseconds_when_interruptable, whichever is first.  Where interrupts
 *     are not available, we sleep for milliseconds_when_polling.
 *   Input Arguments:
 *     milliseconds_when_interruptible: time to wait for interrupt
 *     milliseconds_when_polling: time to wait if interrupts aren't available
 *   Return value:
 *     none
 *   Notes:
 *       The code below is part of a gradual transition from lsleep. In the
 *     future we should be using an event loop.  -rdf, 3/21/94
 *   Modifications:
 *****************************************************************************/
void g2ext_gensym_pause(milliseconds_when_interruptable, milliseconds_when_polling)
    long milliseconds_when_interruptable;
    long milliseconds_when_polling;
{
    g2ext_network_io_trace_note("g2ext_gensym_pause: begin g2ext_sys_sleep");
    g2ext_sys_sleep(milliseconds_when_polling);  /* From networks.c */
    g2ext_network_io_trace_note("g2ext_gensym_pause: end g2ext_sys_sleep");
}


/*
 * The function g2ext_uuid_create gets passed an 8 element array of 16-bit
 * integers (an unsigned short, known to G2 as a wide string).  The 8 elements
 * are populated, with the appropriate byte ordering, with the 16 8-bit bytes
 * that make up a UUID.  If there is no problem, the returned value is 0;
 * otherwise, a non-zero integer is returned.  Currently, this is only
 * implemented for Win32 as a thin wrapper around UuidCreate or
 * UuidCreateSequential; therefore, the high-level code must decode
 * the corresponding Win32 error code return value.
 *
 * g2pvt_uuid_create is defined in msmain.c and stubbed in gsi_w32init.c so that
 * we don't have dependencies in GSI on the actual uuid creation function in the
 * windows library.  But the function called from lisp is defined here to make
 * the translator happy.  yduJ, 3/14/05
 */


#ifdef WIN32
long g2ext_uuid_create (unsigned short *buffer)
{
  /* copied from win32 guiddef.h */
  struct {
    unsigned int Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[6];
  } uuid;

  unsigned char *data4;
  unsigned long data1;
  unsigned short data2, data3;
  long err;

  err = g2pvt_uuid_create((void *)&uuid);

  data1 = uuid.Data1;
  data2 = uuid.Data2;
  data3 = uuid.Data3;
  data4 = uuid.Data4;

  buffer[0] = (unsigned short)((data1 >> 16) & 0xffff);
  buffer[1] = (unsigned short)(data1 & 0xffff);
  buffer[2] = data2;
  buffer[3] = data3;
  buffer[4] = (data4[0] << 8) | data4[1];
  buffer[5] = (data4[2] << 8) | data4[3];
  buffer[6] = (data4[4] << 8) | data4[5];
  buffer[7] = (data4[6] << 8) | data4[7];

  return (long)err;
}
#else

long g2ext_uuid_create (unsigned short *buffer)
{
  buffer[0] = (unsigned short)0;
  buffer[1] = (unsigned short)0;
  buffer[2] = (unsigned short)0;
  buffer[3] = (unsigned short)0;
  buffer[4] = (unsigned short)0;
  buffer[5] = (unsigned short)0;
  buffer[6] = (unsigned short)0;
  buffer[7] = (unsigned short)0;

  /* abort() ?!?!?  That seems extreme!  -jv, 3/13/05 */
  abort();

  return 0L;
}
#endif

/*****************************************************************************
 * g2ext_uuid_eq(unsigned short * uuid1, unsigned short * uuid2)
 *
 * C implementation to compare two uuids.
 *     uuid1 == uuid2      return 1
 *     uuid1 != uuid2      return 2
 *****************************************************************************/

int g2ext_uuid_eq(unsigned short * uuid1, unsigned short *uuid2)
{
#if defined(WIN32)
	return (*((__int64 *)uuid1) != *((__int64 *)uuid2) || 
		*((__int64 *)(uuid1+4)) != *((__int64 *)(uuid2+4)));
#else
	int index;
	for (index = 0; index < 8; ++index)
		if (*(uuid1+index) != *(uuid2+index)) return 1;
	return 0;
#endif
}

//////////////////////////////////////////////////////////
//
// The below functionality is based on RDTSC. Do not call the below
// functions from different threads!
//////////////////////////////////////////////////////////

unsigned long tick_cell_index = 0L;

unsigned long tsc_values[10L];

unsigned long g2ext_get_new_tick_cell_index (void) {
	tick_cell_index++;
	if (tick_cell_index >= 5L) {
		tick_cell_index = 0L;
	}
	return tick_cell_index;
}

long g2ext_get_cpu_ticks_count (void) {

#if defined(WIN32)
	unsigned long cell_index;
	unsigned long tick;

	cell_index = g2ext_get_new_tick_cell_index();

#	if _MSC_VER <= 1200
	_asm {
		rdtsc
		mov tick, eax
	}
#	else
	tick = __rdtsc();
#	endif

	tsc_values[cell_index] = tick;
	return cell_index;
#else
	return 0L; //for Linux/Solaris not implemented at this time
#endif
}

//we don't really use EDX part at this time
//because we assume our instructions to be comparatively fast 
long g2ext_get_tsc_difference(long cell_index_1, long cell_index_2) {
	long lp_diff;//, hp_diff;
	lp_diff = tsc_values[cell_index_2] - tsc_values[cell_index_1];
	//hp_diff = tsc_values[cell_index_2 + 1] - tsc_values[cell_index_1 + 1];

	//in case the result is a negative FIXNUM, it will be ignored on Lisp level,
	//but since a single instruction runs A LOT of time during a typical test,
	//this fact makes no impact on the average peak value
	return lp_diff; 
}


/*

Character codes encrypt/decrypt function 

*/

long g2ext_cc[128][4000][2];

long g2ext_characters_cipher(long code, long refvar, long direction) {
	long result = code;
	long temp, remr;
	
	if (g2ext_cc[code][refvar][direction] != 0)
		return g2ext_cc[code][refvar][direction];
	temp = result - (result < 92L ? 32L : 33L);
	if (direction == DIRECTION_DECRYPT) {
		result = temp - refvar;
		
	} else {
		result = temp + refvar;
	}

	if (direction == DIRECTION_DECRYPT) {
		if (result < 0L) {
			remr = (-result) % 94L;
			if (remr == 0) {
				result = remr;
			} else {
				result = 94L - remr;
			}
		} else {
			result = result % 94L;
		}
	} else {
		result = result % 94L;	
	}

	result = result + (result <= 59L ? 32L : 33L);

	g2ext_cc[code][refvar][direction] = result;
	return result;
}


long g2ext_eval_base_ref_val(long intial_value) {
	return (3943L * intial_value + 3947L) % 3967L;
}

#if SI_SUPPORT_THREAD
/* RTL headers */
#include "config.h"
#endif

int g2ext_max_threads()
{
    return VALUE_CELL_SLOTS;
}

int g2ext_number_of_cores()
{
    return 8; /* TODO: how to get it from OS calls? */
}

/* Locale must be set to default (C), otherwise some I/O functions on float values
   may not work correctly in european locales. -- Chun Tian (binghe), Dec 2015 */
void g2ext_initialize_locales()
{
    setlocale(LC_ALL, "C");
}

/* TODO: clean up all use of "mbstate_t" on Linux */
#include <wchar.h>

char *g2_s16dup2mbs(g2chr16_t const *g2s)
{
    g2chr16_t const *converter;
    mbstate_t mbs;
    char *s;
    char *rslt;
    size_t total;
    size_t length;

    assert(g2s != NULL);

    /* We calculate the size of the converted string first, because
       allocating for `s16len(g2s) * MB_LEN_MAX` characters can be
       very wasteful - on Linux, `MB_LEN_MAX == 16`.
    */
    memset(&mbs, 0, sizeof mbs);
    converter = g2s;
    total = 0;
    while (*converter != 0) {
        char dummy[MB_LEN_MAX];
        length = wcrtomb(dummy, *converter++, &mbs);
        if (length == (size_t)-1) {
            return NULL;
        }
        total += length;
    }

    rslt = (char *)malloc(total+1);
    if (NULL == rslt) {
        return NULL;
    }

    converter = g2s;
    s = rslt;
    memset(&mbs, 0, sizeof mbs);
    while (*converter != 0) {
        length = wcrtomb(s, *converter++, &mbs);
        assert(length != (size_t)-1);
        s += length;
    }
    *s = '\0';

    return rslt;
}


char *g2pvt_chomp(char *s)
{
    assert(s != NULL);
    return g2pvt_chomp_ex(s, strlen(s), "\n\r");
}


size_t g2pvt_s16len(g2chr16_t const* str)
{
    size_t n = 0;

    assert(str != NULL);
    while (*str != 0) {
        ++str;
        ++n;
    }
    return n;
}

g2chr16_t *g2pvt_chomps16(g2chr16_t *g2s)
{
    g2chr16_t to_chomp[] = { '\n', '\r', 0x2028, 0x2029, 0 };
    assert(g2s != NULL);
    return g2pvt_chomps16_ex(g2s, g2pvt_s16len(g2s), to_chomp);
}


char *g2pvt_chomp_ex(char *s, size_t n, char const* chars_to_chomp)
{
    char *p = s + n;

    assert(s != NULL);

    while (p > s) {
        --p;
        if (NULL != strchr(chars_to_chomp, *p)) {
            *p = '\0';
        }
        else {
            break;
        }
    }
    return s;
}


g2chr16_t *g2pvt_chomps16_ex(g2chr16_t *g2s, size_t n, g2chr16_t const* chars_to_chomp)
{
    g2chr16_t *p = g2s + n;

    assert(g2s != NULL);

    while (p > g2s) {
        --p;
        if (NULL != g2pvt_s16chr(chars_to_chomp, *p)) {
            *p = '\0';
        }
        else {
            break;
        }
    }
    return g2s;
}


char* g2pvt_dup_chomp_ex(char const *src, size_t n, char const *chars_to_chomp)
{
    char *dst;
    char const *p = src + n;
    size_t to_copy;

    assert(src != NULL);

    dst = malloc(sizeof(char) * (n+1));
    if (NULL == dst) {
        return NULL;
    }
    
    while (p > src) {
        if (NULL == strchr(chars_to_chomp, p[-1])) {
	    break;
        }
        --p;
    }
    to_copy = p - src;
    if (to_copy > 0) {
        memcpy(dst, src, to_copy);
    }
    dst[to_copy] = '\0';

    return dst;
}


g2chr16_t *g2pvt_s16chr(g2chr16_t const*str, int character)
{
    while (*str != 0) {
        if (*str == character) {
            /* Yes, I know, this is UB, but, I didn't design `strchr`
               and it works, because we never really pass a
               "physically constant" string here.
            */
            return (g2chr16_t*)str;
        }
        ++str;
    }
    return NULL;
}


g2chr16_t* g2pvt_dup_chomps16_ex(g2chr16_t const* src, size_t n, g2chr16_t const *chars_to_chomp)
{
    g2chr16_t *dst;
    g2chr16_t const *p = src + n;
    size_t to_copy;

    assert(src != NULL);

    dst = malloc((sizeof *dst) * (n+1));
    if (NULL == dst) {
        return NULL;
    }
    
    while (p > src) {
        if (NULL == g2pvt_s16chr(chars_to_chomp, p[-1])) {
	    break;
        }
        --p;
    }
    to_copy = p - src;
    if (to_copy > 0) {
        memcpy(dst, src, to_copy * sizeof *dst);
    }
    dst[to_copy] = '\0';

    return dst;
}


int g2pvt_s16cmp(g2chr16_t const *s1, g2chr16_t const* s2)
{
    size_t n;
    size_t i;
    assert(s1 != NULL);
    assert(s2 != NULL);

    n = g2pvt_s16len(s1);
    for (i = 0 ; i < n+1; ++i) {
        int diff = s1[i] - s2[i];
        if (diff != 0) {
            return diff;
        }
    }

    return 0;
}



/* GENSYMCID-1856: G2 built in VDI2 Linux VM can't run in older Linux boxes
 *
 * Here, we use a wrapper function to force using the old version of memcpy()
 * which is ABI compatible with glibc 2.2.5-2.13, so that G2 built in higher
 * glibc versions (works for 2.14) can still run in older glibc environment.
 *
 * GCC LD option `-Wl,--wrap=memcpy' is needed for the wrapper to actually work,
 * then use `objdump -t g2 | grep memcpy` to confirm ("g2" is the target program).
 *
 * -- Chun Tian (binghe), August 8, 2016.
 */

/* The abovementioned fix didn't link on Ubuntu 16.04 with LSB 5.0 and gcc 4.4.7
 *  So, we use a wrapper function to substitute all memcpy calls with memmove.
 */

#if defined(Platform_Linux)

#if (__LSB_VERSION__ >= 50) || (!defined __LSB_VERSION__)

void *__wrap_memcpy(void *dest, const void *src, size_t n)
{ 
  return memmove(dest, src, n);
}

#else

#if defined(Platform_64bit)
  void *__memcpy_glibc_2_2_5(void *, const void *, size_t);
  asm(".symver __memcpy_glibc_2_2_5, memcpy@GLIBC_2.2.5");
#else
  void *__memcpy_glibc_2_0(void *, const void *, size_t);
  asm(".symver __memcpy_glibc_2_0, memcpy@GLIBC_2.0");
#endif

void *__wrap_memcpy(void *dest, const void *src, size_t n)
{
  
#if defined(Platform_64bit)
    return __memcpy_glibc_2_2_5(dest, src, n);
#else
    return __memcpy_glibc_2_0(dest, src, n);
#endif
  
}

#endif

#endif
