/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      g2signal.c
 +
 + Author(s):   John Hodgkinson
 +
 + Description: 
 + 
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
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
 +   Section:      FUNCTION GROUP - Signal Catching
 +      g2ext_most_recent_signal_code()      0000000
 +      g2ext_gensym_signal_handler()         0000000
 +      g2ext_gensym_SIGALRM_handler()        0000000
 +      g2ext_establish_signal_handler()     0000000 Mixed ifdefs
 +      g2ext_gensym_sig_handler_for_launch() 0000000
 +      g2ext_establish_launch_sig_handler() 0000000
 +   Section:      FUNCTION GROUP - Signal Catching
 +      g2ext_cause_future_alarm_signal()    0000000 Multiply Defined
 +      g2ext_cancel_future_alarm_signal()   0000000 Multiply Defined
 +      
 + External Interface:
 + 
 +
 + Dependencies: none
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   4/05/96, mpc: Major structural reorganization to improve code legibility
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
#include "g2signal.h"
#include <signal.h>

#if !defined(sun)
#  include <stdlib.h>
#endif

#if defined(unix)
#  include <sys/time.h> /* for timeout interrupts */
#  include <sys/signal.h>
#  include <sys/types.h>
#  ifdef __STDC__
#    include <unistd.h>
#  endif
#endif /* unix */


extern int g2ext_establish_sigchld_handler(void);


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

#define CAUSE_FUTURE_ALARM_SIGNAL_SUCCESS 0
#define CAUSE_FUTURE_ALARM_SIGNAL_FAILURE -1
#define CANCEL_FUTURE_ALARM_SIGNAL_SUCCESS 0
#define CANCEL_FUTURE_ALARM_SIGNAL_FAILURE -1


#if defined(unix)
#   define SETITIMER_SUCCESS 0
#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(unix)
struct itimerval     g2ext_gensym_internal_timer;
#endif

long g2ext_Most_recent_signal_code = 0;


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Signal Catching
 %
 % Description:
 %   C side of the signal-catching mechanism for Chestnut.
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
 * long g2ext_most_recent_signal_code()
 *
 *   Description:
 *     Accesses the code of the most recent signal encountered by G2.
 *   Input Arguments:
 *     
 *   Returns:
 *     
 *   Notes: 
 *       8/16/93, jh per jra: Added g2ext_most_recent_signal_code(), which
 *     accesses the code of the most recent signal encountered by G2.  This is
 *     so we don't have to pass a value back through the def-foreign-callable
 *     mechanism, which is not standard across Lisps.  This addition should
 *     obviate the need for the function convert_long_to_fixnum(), defined in
 *     /bt/ab/runtime/c/gensym.c, and the macro CALL_G2_SIGNAL_HANDLER(),
 *    defined in /bt/ab/ext/c/cprim.h.
 *    -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

long g2ext_most_recent_signal_code()
{
  return g2ext_Most_recent_signal_code;
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_gensym_signal_handler(signal_code)
 *
 *   Description:
 *     
 *   Input Arguments:
 *     signal_code:
 *   Returns:
 *     
 *   Notes: 
 *    -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

extern long g2int_signal_handler();

#if !defined(WIN32)
/* Comes from backtrac.o: */
extern int g2ext_save_backtrace_into_array(/* void **, int, int */);
#endif

extern void *g2ext_pc_at_c_gensym_signal_handler;
extern void *g2ext_saved_backtrace_array[];
extern int g2ext_saved_backtrace_array_fcount;
extern int g2ext_saved_backtrace_array_fsize;
extern int function_tracing_enabled;

#if defined(sun4)

void g2ext_gensym_signal_handler(signal_code,signal_code_info,scp,addr)
    int signal_code, signal_code_info;
    struct sigcontext *scp;
    char *addr;
{
  g2ext_saved_backtrace_array_fcount =
    g2ext_save_backtrace_into_array(g2ext_saved_backtrace_array,
			      g2ext_saved_backtrace_array_fsize,
			      0);
  g2ext_pc_at_c_gensym_signal_handler = (void *)(scp->sc_pc);
  g2ext_Most_recent_signal_code = signal_code;
  function_tracing_enabled = FALSE;
  g2int_signal_handler();
}

#else 
#  if defined(sparcsol)
#    include "ucontext.h"

void g2ext_gensym_signal_handler(signal_code, sip, uap)
   int signal_code;
   siginfo_t *sip;
   ucontext_t *uap;
{
  g2ext_saved_backtrace_array_fcount =
    g2ext_save_backtrace_into_array(g2ext_saved_backtrace_array,
			      g2ext_saved_backtrace_array_fsize,
			      0);
  g2ext_pc_at_c_gensym_signal_handler = (void *)(uap->uc_mcontext.gregs[REG_PC]);
  g2ext_Most_recent_signal_code = signal_code;
  function_tracing_enabled = FALSE;
  g2int_signal_handler();
}

#  else
/* defined(hp9000s800) could be here, if I could figure out which register is the PC! */
/*   See /usr/include/sys/signal.h   Maybe it is sc_gr31? */
/* defined(alphaosf) compiles OK, but always returns 0.   */
#    if defined(hp9000s800) && 0

void g2ext_gensym_signal_handler(signal_code,signal_code_info,scp)
    int signal_code, signal_code_info;
    struct sigcontext *scp;
{
  g2ext_saved_backtrace_array_fcount =
    g2ext_save_backtrace_into_array(g2ext_saved_backtrace_array,
			      g2ext_saved_backtrace_array_fsize,
			      0);
#      if defined(hp9000s800)
  g2ext_pc_at_c_gensym_signal_handler = (void *)(scp->sc_gr31);
#      else
  g2ext_pc_at_c_gensym_signal_handler = (void *)(scp->sc_pc);
#      endif
  g2ext_Most_recent_signal_code = signal_code;
  function_tracing_enabled = FALSE;
  g2int_signal_handler();
}

#    else

void g2ext_gensym_signal_handler(int signal_code)
{
#      if defined (WIN32)
  g2ext_saved_backtrace_array_fcount = 0;
#      else
  g2ext_saved_backtrace_array_fcount =
    g2ext_save_backtrace_into_array(g2ext_saved_backtrace_array,
			      g2ext_saved_backtrace_array_fsize,
			      0);
  g2ext_pc_at_c_gensym_signal_handler = 0;
#      endif
  g2ext_Most_recent_signal_code = signal_code;
  function_tracing_enabled = FALSE;
  g2int_signal_handler();
}

#    endif
#  endif
#endif

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_gensym_SIGALRM_handler(signal_code)
 *
 *   Description:
 *     
 *   Input Arguments:
 *     
 *   Returns:
 *     
 *   Notes: 
 *       g2int_service_sigalrm_signal() is a translated Lisp function from the
 *     Lisp module OS-ERROR.  For further details, see the doc there.
 *     -----
 *   Modifications:
 *       4/26/93,jh: Added special-casing for SIGALRM signal handler.
 *     -----
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

extern long g2ext_gensym_SIGALARM_was_seen;

void g2ext_gensym_SIGALRM_handler(signal_code)
  int     signal_code;
{
  extern long g2int_service_sigalrm_signal();
  g2ext_gensym_SIGALARM_was_seen = TRUE; /* so select can tell what interrupted it */
  g2int_service_sigalrm_signal();
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_establish_signal_handler (long signal_code)
 *
 *   Description: establishes which signal handler function to be invoked for
 *     the given signal
 *   Input Arguments: signal_code, the value of the signal to be handled
 *   Returns: always returns 0
 *   Notes: Windows only supports a subset of the signals we try to register;
 *     with Visual C++ 6.0, it didn't care about that, but as of Visual C++ 8,
 *     this is considered a run-time error.  We could do an #ifdef MSVC8, but
 *     I don't see any point to the registration in any version. Windows doesn't
 *     provide any signals which use those values.  -jv, 10/05/06
 *    -----
 *   Modifications: reduce #ifdeffedness by making a WIN32 and POSIX versions
 *     separate. Use "POSIX" because that's what g2ext_establish_sigchld_handler
 *     uses.  -jv, 10/05/06
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

#ifdef POSIX
long g2ext_establish_signal_handler (signal_code)
  long     signal_code;
{
  switch (signal_code) {

  case SIGPIPE:
    signal(SIGPIPE, SIG_IGN);
    break;

  case SIGCHLD:
    g2ext_establish_sigchld_handler();
    break;

  default:
    {
      struct sigaction siga, old_siga;
      sigemptyset(&siga.sa_mask);
      siga.sa_flags = 0;
      if (signal_code == SIGALRM) {
        siga.sa_handler = g2ext_gensym_SIGALRM_handler;
#ifdef SA_RESTART
        siga.sa_flags |= SA_RESTART;
#endif
      } else {
#ifdef sparcsol /* provides platform-specific extra args to the signal handler */
        siga.sa_sigaction = g2ext_gensym_signal_handler;
        siga.sa_flags |= SA_SIGINFO;
        siga.sa_flags |= SA_NODEFER;
#else
        siga.sa_handler = g2ext_gensym_signal_handler;
#endif
      }
      sigaction(signal_code, &siga, &old_siga);
    }
    break;
  }
  return 0;
}
#endif /* POSIX */

#ifdef WIN32

int windowsSupportedSignals[WINDOWS_SUPPORTED_SIGNALS_COUNT] = {SIGINT,
		SIGILL, SIGFPE,	SIGSEGV, SIGTERM, SIGBREAK, SIGABRT};

int isSignalSupportedByWindows(int signalNumber) {
	int i = 0;
	for (; i < WINDOWS_SUPPORTED_SIGNALS_COUNT; ++i) {
		if (windowsSupportedSignals[i] == signalNumber) return 1;
	}
	return 0;
}

long g2ext_establish_signal_handler(long signal_code)
{
    if (isSignalSupportedByWindows(signal_code))
		signal(signal_code, g2ext_gensym_signal_handler);

	return 0;
}
#endif /* WIN32 */

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_unestablish_signal_handler(long signal_code)
 *
 *   Description: Removes Gensym-specific signal handling for the given signal.
 *     
 *   Input Arguments:
 *     signal_code
 *   Returns:
 *     
 *   Notes: This function only works on UNIX.
 * 
 *   Modifications:
 *****************************************************************************/

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

long g2ext_unestablish_signal_handler(signal_code)
  long     signal_code;
{
#if defined(SA_FULLDUMP)
  struct sigaction siga, old_siga;
  sigemptyset(&siga.sa_mask);
  siga.sa_flags = SA_FULLDUMP;
  siga.sa_handler = SIG_DFL;
  sigaction(signal_code, &siga, &old_siga);
#else

#	ifdef WIN32
	if (isSignalSupportedByWindows(signal_code))
#	endif
	{
		signal(signal_code, SIG_DFL);
	}
#endif

  return 0; 
}

/*0000000000000000000000000000 Mixed ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_gensym_sig_handler_for_launch(signal_code)
 *
 *   Description:
 *     
 *   Input Arguments:
 *     signal_code
 *   Returns:
 *     
 *   Notes: 
 *       g2ext_gensym_sig_handler_for_launch() calls g2int_signal_handler_for_launch(),
 *     a translated Lisp function, which throws to the G2 error catchpoint.
 *     The next statement (return 0) is never reached.
 *    -----
 *   Modifications:
 *       4/3/91.  Added a signal handler for launch time: this is simpler,
 *     since we have no post-mortem mechanism set up yet.
 *    -----
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

void g2ext_gensym_sig_handler_for_launch(int signal_code)
{
  extern long g2int_signal_handler_for_launch();

  g2ext_Most_recent_signal_code = signal_code;
  g2int_signal_handler_for_launch();
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*****************************************************************************
 * long int g2ext_establish_launch_sig_handler(signal_code)
 *
 *   Description:
 *     
 *   Input Arguments:
 *     signal_code
 *   Returns:
 *     
 *   Notes: 
 *    -----
 *   Modifications:
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

long int g2ext_establish_launch_sig_handler(signal_code)
  long int     signal_code;
{
  switch (signal_code) {

# if !defined(_WINSOCKAPI_)
  case SIGPIPE:
    signal(SIGPIPE, SIG_IGN);
    break;
# endif
    /* The following is funky, but SIGCHLD is not standard on non-Unix
     * platforms, and os-error.lisp uses 18 for SIGCHLD.
     */
# ifdef unix
  case SIGCHLD:
# else
  case 18:
# endif
    g2ext_establish_sigchld_handler(); 
    break;

  default:
#ifdef WIN32
    /* Filter all invalid signal_code on win32. -- binghe, 2009/6/28 */ 
    switch (signal_code) {
      case SIGABRT:
      case SIGFPE:
      case SIGILL:
      case SIGINT:
      case SIGSEGV:
      case SIGTERM:
	signal(signal_code, g2ext_gensym_sig_handler_for_launch);
	break;
      default:
        break;
    }
#else
    signal(signal_code, g2ext_gensym_sig_handler_for_launch);
#endif
    break;
  }
  return 0; 
}

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Timeout Interrupts
 %
 % Description:
 %   
 % Notes:
 %     4/26/93,jh: Currently, nether g2ext_cause_future_alarm_signal() nor
 %   g2ext_cancel_future_alarm_signal() work on non-UNIX platforms.
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long g2ext_cause_future_alarm_signal(milliseconds)
 *
 *   Description:
 *     
 *   Input Arguments:
 *     milliseconds
 *   Returns:
 *     Returns 0 if successful, -1 otherwise.
 *   Notes: 
 *    -----
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(unix)

long g2ext_cause_future_alarm_signal(milliseconds)
  long     milliseconds;
{
  long     status;

  g2ext_establish_signal_handler(SIGALRM);
  g2ext_gensym_internal_timer.it_interval.tv_sec = 0;
  g2ext_gensym_internal_timer.it_interval.tv_usec = 0;
  g2ext_gensym_internal_timer.it_value.tv_sec = 0;
  g2ext_gensym_internal_timer.it_value.tv_usec = 1000 * milliseconds;
  status = setitimer(ITIMER_REAL, &g2ext_gensym_internal_timer, NULL);
  if (status == SETITIMER_SUCCESS)
    return CAUSE_FUTURE_ALARM_SIGNAL_SUCCESS;
  else
    return CAUSE_FUTURE_ALARM_SIGNAL_FAILURE;
}

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#else /* not unix */

long g2ext_cause_future_alarm_signal(milliseconds)
  long     milliseconds;
{
  return CAUSE_FUTURE_ALARM_SIGNAL_FAILURE;
}

#endif /* unix */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*****************************************************************************
 * long g2ext_cancel_future_alarm_signal()
 *
 *   Description:
 *     
 *   Input Arguments:
 *     none
 *   Returns:
 *     Returns 0 if successful, -1 otherwise.
 *   Notes: 
 *    -----
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(unix)

long g2ext_cancel_future_alarm_signal()
{
  long     status;
  
  g2ext_gensym_internal_timer.it_value.tv_sec = 0;
  g2ext_gensym_internal_timer.it_value.tv_usec = 0;
  g2ext_gensym_internal_timer.it_interval.tv_sec = 0;
  g2ext_gensym_internal_timer.it_interval.tv_usec = 0;
  status = setitimer(ITIMER_REAL, &g2ext_gensym_internal_timer, NULL);
  if (status == SETITIMER_SUCCESS)
    return CANCEL_FUTURE_ALARM_SIGNAL_SUCCESS;
  else
    return CANCEL_FUTURE_ALARM_SIGNAL_FAILURE;
}

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#else /* not unix */

long g2ext_cancel_future_alarm_signal()
{
  return CANCEL_FUTURE_ALARM_SIGNAL_FAILURE;
}

#endif /* unix */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
