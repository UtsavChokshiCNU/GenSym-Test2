/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      cprocess.c
 +
 + Author(s):   Mike Colena, John Hodgkinson, Mark Staknis
 +
 + Description: This module contains the functions for managing processes
 +              and process signals.
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
 +   Section:      FUNCTION GROUP - Process Creation and Access
 +      g2ext_unix_cmd_with_string_output()   0000000 Multiply Defined
 +      g2ext_run_command_line()              0000000 Multiply Defined
 +      g2ext_substatus_run_command_line()    0000000 Mixed Ifdefs
 +      g2ext_spawn_command_directly()        0000000 Multiply Defined
 +      g2ext_spawn_command_line_process()    0000000 Multiply Defined
 +      g2ext_kill_spawned_command_line()     0000000 Mixed Ifdefs
 +      g2ext_process_exists()                0000000 Multiply Defined
 +
 +   Section:      FUNCTION GROUP - Process Signal Management
 +      sigchld_handler()                  1111111 Conditionally Defined
 +      g2ext_establish_sigchld_handler()     0000000 Multiply Defined
 +
 +   Section:      FUNCTION GROUP - Unused Process Access
 +      g2ext_get_vms_process_name()          0000000 Multiply Defined
 +      g2ext_set_vms_process_name()          0000000 Multiply Defined
 +      g2ext_get_next_vms_process_tag()      0000000 Multiply Defined
 +   
 + External Interface:
 + 
 +      long     g2ext_unix_cmd_with_string_output(char *command, char *buff)
 +                 This forks a child with a pipe to the parent, the child
 +                 executes a system() command with output directed to the
 +                 pipe, and the parent reads the pipe and returns the string
 +                 that it read.
 +
 +      int      g2ext_run_command_line
 +                 Uses the system() call to execute a command line and
 +                 waits for call to complete.
 +
 +      int      g2ext_substatus_run_command_line(char *command_string)
 +                 Uses g2ext_run_command_line and returns the status of
 +                 the subprocess or special values for errors.
 +
 +      double   g2ext_spawn_command_directly(char *command_string)
 +                 Runs command_string as a detached process without
 +                 invoking a "shell".  Arguments, possibly quoted,
 +                 are passed directly without shell interpretation.
 +
 +      double   g2ext_spawn_command_line_process(char *command_string)
 +                 Runs command_string as a detached process in a "shell".
 + 
 +      long     g2ext_kill_spawned_command_line(double pid)
 +                 Terminates a process started with
 +                 g2ext_spawn_command_line_process().
 +
 +      int      g2ext_establish_sigchld_handler()
 +                 Sets up the SIGCHLD signal handler on platforms that have
 +                 the signal.
 +
 +      int      g2ext_process_exists()
 +                 Checks for process existence.
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
 +   6/15/94, mes:  Created this module to remove functions from cprim.c,
 +                  reduce its size, and improve functional organization.
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

#include <stdlib.h>

#if defined(WIN32)
#  include <windows.h>
#  include "msincls.h"
#  include <string.h>
#  include <ctype.h>
#  include <process.h>
#endif

/*--------------- UNIX --------------*/
#if defined(unix)

#  include <sys/types.h>

/* for process-spawning machinery */
#  include <unistd.h>      /* Needed for vfork(), at least. */
#  include <signal.h>      /* Needed for SIGCHLD handler. */
#  include <sys/signal.h>
#  include <sys/wait.h>
#  include <errno.h>       /* Needed for SIGCHLD handler. */
#  include <ctype.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <sys/time.h>

#  if !defined(__hpux)
#    include <dlfcn.h>
#  endif

#  if defined(_IBMR2)
#    include <sys/select.h> /* only needed on this platform */
#    define vfork fork
#  endif

#endif /* unix */

#include <stdarg.h>
#include <string.h>


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
#define IN_PROGRESS 1

#define MAX_ARGS 100        /* Needed by g2ext_spawn_command_directly. */
#define MAX_ARG_LEN 100

#define MAX_STRING_FROM_PIPE 2048

/* 60s wait time to complete the command in g2ext_substatus_run_command_line() */
#define WAIT_TIME_COMMAND 1*60*1000

#if defined(WIN32)
#  define COMMAND_LINE_FAILED(result) result
#  define DEFAULT_EXTENSION ".dll"
#  define DEFAULT_EXTENSION_LENGTH 4
#  define HANDLE_TYPE     HINSTANCE
#  define DLOPEN(name)    LoadLibrary(name)
#  define DLCLOSE(handle) FreeLibrary(handle)
#  define DLSYM           GetProcAddress
#  define DLERROR         gensym_dlerror()
#  define GETPID          _getpid()
#else
#  define DEFAULT_EXTENSION ".so"
#  define DEFAULT_EXTENSION_LENGTH 3
#  define HANDLE_TYPE     void *
#  define DLOPEN(name)    dlopen(name,1)
#  if defined(_IBMR2)
#    define DLCLOSE(handle) ((void *) handle)
#  else
#    define DLCLOSE(handle) dlclose(handle)
#  endif
#  define DLSYM           dlsym
#  define DLERROR         dlerror()
#  define GETPID          getpid()
#  if defined(sparcsol)
#    define COMMAND_LINE_FAILED(result) result
#  elif defined(sun4)
#    define COMMAND_LINE_FAILED(result) ((result!=0) && (result!=-1))
#  else
#  endif
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

#ifdef WIN32
static BOOL inherit_stdio_handles = TRUE;
BOOL logging_to_file = TRUE;
#endif

extern long g2ext_write_string_to_console(/* char * */);


double g2ext_get_process_identifier()
{
#ifndef WIN32
  return (double)getpid();
#else
  return (double)_getpid();
#endif
}

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Process Creation and Access
 %
 % Description:
 %      These functions control execution and control of spawned
 %      subprocesses
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
 * int g2ext_unix_command_with_string_output(char *command, char *buff)
 *
 *   Description:
 *     This forks a child with a pipe to the parent, the child
 *     executes a system() command with output directed to the pipe, and 
 *     the parent reads the pipe and returns the string that it read.
 *   Input Arguments:
 *     command:  Command to be executed by system
 *     buff:     buffer in which to pass back command's output
 *   Returns:
 *     buff: null-terminated string printed by child
 *     return value: SUCCESS or FAILURE
 *   Notes: 
 *     For the file-io facility for G2 users.
 *     Is the setpgrp() really needed for a clean exit?  Does it have
 *        any useful effect?  Is it an attempt to get rid of zombies? 
 *     Is there a reason that the system() command should have a
 *        separate process group, since it doesn't seem to receive special
 *        signals?
 *     The close() commands should not use integer args, and dup
 *        may possibly be replaced by dup2().
 *     Because the parent does a blocking read from the pipe, it may
 *         hang indefinitely if the child does.
 *   Modifications:
 *     mpc 11/22/93: Replaced call to setpgrp() with setpgid().
 *         setpgrp() was different on SYSV and BSD platforms,
 *         setpgid() is POSIX.
 *****************************************************************************/
typedef long (timeout_callback_fn)();
#define ONE_DAY_TIMEOUT (60 * 60 * 24)
extern long g2ext_unix_cmd_with_string_output_and_timeout_callback();  /* to be phased out. -mhd, 2/10/01 */
extern long g2ext_unix_cmd_with_string_output_and_timeout_callback_mx(); 


long g2ext_unix_cmd_with_string_output(command, buff)
     char    *command;
     char    *buff;
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback(command, TRUE, (char *)0, buff, 
							   ONE_DAY_TIMEOUT, 0);
}

long
g2ext_unix_cmd_with_string_output_mx (char *command, char *buff, long max_bytes)
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback_mx
    (command, TRUE, (char *)0, buff, ONE_DAY_TIMEOUT, 0, max_bytes);
}

extern long g2int_unix_command_callback();


long
g2ext_unix_cmd_with_string_output_and_timeout
(char *command, char *dir, char *buff, long timeout)
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback
    (command, TRUE, dir, buff, timeout, g2int_unix_command_callback);
}

extern long g2int_unix_command_callback_mx();

long
g2ext_unix_cmd_with_string_output_and_timeout_mx
(char *command, char *dir, char *buff, long timeout, long max_bytes)
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback_mx
    (command, TRUE, dir, buff, timeout, g2int_unix_command_callback, max_bytes);
}

long g2ext_run_program_with_string_output_and_timeout(command, dir, buff, timeout)
     char    *command;
     char    *dir;
     char    *buff;
     long    timeout;
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback(command, FALSE, dir, buff, 
							   timeout, g2int_unix_command_callback);
}

long
g2ext_run_program_with_string_output_and_timeout_mx
(char *command, char *dir, char *buff, long timeout, long max_bytes)
{
  return
    g2ext_unix_cmd_with_string_output_and_timeout_callback_mx
    (command, FALSE, dir, buff, timeout, g2int_unix_command_callback, max_bytes);
}

/* The use of this should be phased out throughout! -mhd, 2/10/01 */
#define MX_MAX_BYTES 5000

long g2ext_unix_cmd_with_string_output_and_timeout_callback(command, command_p, dir, 
							    buff, timeout_in_ms, timeout_callback)
     char    *command;
     int     command_p;
     char    *dir;
     char    *buff;
     long    timeout_in_ms;
     timeout_callback_fn *timeout_callback;
{
  return(g2ext_unix_cmd_with_string_output_and_timeout_callback_mx
	 (command, command_p, dir, buff, timeout_in_ms, timeout_callback, MX_MAX_BYTES));
}



/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#ifdef POSIX

/* ARGSUSED */
long
g2ext_unix_cmd_with_string_output_and_timeout_callback_mx(command, fnord, directory, buf, timeout, callback, len)
    char *command;
    int fnord; 
    char *directory, *buf;
    long timeout;
    long (*callback)();
    size_t len;
{
  struct timeval end, now, select_timeout;
  ssize_t nbytes, delta = 0;
  long ms;
  fd_set pipe_fd_set;
  /* char *argp[] = {"sh", "-c", NULL, NULL}; */
  int fd[2];
  pid_t pid;

  /* argp[3] = command; */

  if (pipe(fd) < 0)
    return(FAILURE);

  if ((pid = vfork()) == 0) {	/* we're the child process */
    close(fd[0]);
    setpgid(getpid(), getpid());
    close(fileno(stdout));
    close(fileno(stderr));
    dup2(fd[1], fileno(stdout));	/* redirect stdout */

    if (directory)
      chdir(directory);

    /* execve("/bin/sh", argp, environ); */
    system(command);

    _exit(0);
  } else {			/* we're the parent process */
    close(fd[1]);
    fcntl(fd[0], F_SETFL, O_NONBLOCK | fcntl(fd[0], F_GETFL, 0));
    
    gettimeofday(&end, 0);
    TIMEVAL_ADDMSEC(&end, timeout);
      
    for (;;)
      if ((nbytes = read(fd[0], buf + delta, len - delta)) == 0)
	break;
      else if (nbytes < 0) {
	if (errno == EAGAIN) {
	retry:
	  gettimeofday(&now, 0);
	  if (TIMEVAL_GE(&now, &end)) {
	    if (callback && (ms = (*callback)())) {
		TIMEVAL_ADDMSEC(&end, ms);
	    } else {
	      kill(-pid, SIGKILL); /* kill child process group */
	      break;
	    }
	  } else {
	    memcpy(&select_timeout, &end, sizeof(struct timeval));
	    TIMEVAL_SUB(&select_timeout, &now);
	    FD_ZERO(&pipe_fd_set);
	    FD_SET(fd[0], &pipe_fd_set);
	    if (!select(fd[0] + 1, &pipe_fd_set, NULL, &pipe_fd_set, &select_timeout))
	      goto retry;
	  }
	} else if (errno != EINTR) {
	  break;
	}
      } else
	delta += nbytes;

    close(fd[0]);

    if (delta == 0)
      return(FAILURE);
    else {
      *(buf + (sizeof(char) * delta)) = '\0';
      return(SUCCESS);
    }
  }

  return 0;
}

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#else
#   if defined(WIN32)
static char *name_for_pipe = 0;
static char *get_name_for_pipe()
{
  if (!name_for_pipe) 
    name_for_pipe = "\\\\.\\pipe\\g2ext_unix_cmd_pipe";
  return name_for_pipe;
}

long g2ext_unix_cmd_with_string_output_and_timeout_callback_mx(command, command_p, dir,
							       buff, timeout_in_ms, timeout_callback,
							       max_bytes)
     char    *command;
     int     command_p;
     char    *dir;
     char    *buff;
     long    timeout_in_ms;
     timeout_callback_fn *timeout_callback;
     int max_bytes;
{
  HANDLE   hPipeWrite, hPipeRead;
  PROCESS_INFORMATION ProcInfo;
  STARTUPINFO StartInfo;
  SECURITY_ATTRIBUTES saAttr;
  OVERLAPPED gOverlapped;
  char    cmd_command[512];
  char    string_from_pipe[MAX_STRING_FROM_PIPE];
  int     bytes_read, bytes_read_so_far = 0;
  int status = IN_PROGRESS;
  DWORD creation_flags;

  /* Since NT CreateProcess() cannot execute shell commands, 
   *  we prepend all commands with the "cmd /c" program,
   *  which is a one-shot command shell interpreter.
   */ 
  cmd_command[0] = '\0';
  if (command_p) {
    strcat( cmd_command, "cmd /c ");
  }
  strcat( cmd_command, command );

  /* Our pipe needs this security attributes struct. In order for
   *  the child process to write to this pipe, the InheritHandle
   *  flag must be TRUE.
   */
  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = NULL;
  hPipeWrite = CreateNamedPipe(get_name_for_pipe(),
			       PIPE_ACCESS_OUTBOUND,PIPE_WAIT,1,
			       2048,2048,500,&saAttr);
  hPipeRead = CreateFile(get_name_for_pipe(),
			 GENERIC_READ,
			 0,
			 &saAttr,
			 OPEN_ALWAYS,
			 FILE_FLAG_OVERLAPPED,
			 0);
  if ( hPipeRead != INVALID_HANDLE_VALUE ) {

    /* We must pass this humongous STARTUPINFO struct to the
     *  CreateProcess() function. Most of the elements are
     *  ignored but must be initialized.
     */
    memset(&StartInfo, 0, sizeof(StartInfo));
    StartInfo.cb = sizeof(StartInfo);

    /* These members are important. By using USESTDHANDLES flag,
     *  we tell the child process to use as stdin/stdout/stderr
     *  the handles we pass.
     * Note here that the handles to the pipe we created must 
     *  have been created with security attribute "inherit"
     *  set to true.
     */
    StartInfo.dwFlags = STARTF_USESTDHANDLES;
    StartInfo.hStdOutput = hPipeWrite;
    StartInfo.hStdError = hPipeWrite;

    if (logging_to_file) 
      creation_flags = CREATE_NO_WINDOW;
    else
      creation_flags = 0;

    if ( CreateProcess(NULL, cmd_command, NULL, NULL, TRUE,
		       creation_flags, NULL, dir,
		       &StartInfo, &ProcInfo) == TRUE ) {
	
      /* Since we will run concurrently with the new process,
       *  we release our handles. Note we MUST release our
       *  handles or waste system resources.
       */
      CloseHandle(ProcInfo.hThread);
      CloseHandle(ProcInfo.hProcess);

      /* We need to close our instance of the inheritable write pipe
       *  write handle now that its been inherited so that all open
       *  handles to the pipe are closed when the child process ends
       *  and closes its handles to the pipe.
       */
      CloseHandle(hPipeWrite);
      hPipeWrite = INVALID_HANDLE_VALUE;

      gOverlapped.Offset     = 0; 
      gOverlapped.OffsetHigh = 0; 
      gOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	    
      /* See "Server Using Overlapped Input and Output" */
      while (status == IN_PROGRESS) {
	int read_result, last_error = 0;
	if (read_result = ReadFile( hPipeRead, string_from_pipe+bytes_read_so_far, 
				    MAX_STRING_FROM_PIPE, &bytes_read, 
				    &gOverlapped))
	  bytes_read_so_far += bytes_read;
	else 
	  switch (last_error = GetLastError()) {
	  case ERROR_HANDLE_EOF: 
	  case ERROR_BROKEN_PIPE: status = SUCCESS; break;
	  case ERROR_IO_PENDING:
	    while (WAIT_TIMEOUT == WaitForSingleObject(gOverlapped.hEvent,timeout_in_ms)) {
	      if (timeout_callback != 0)
		timeout_in_ms = (*timeout_callback)();
	      if (timeout_in_ms <= 0) {
		/* kill(-pid,SIGKILL); */
		status = FAILURE;
		break;
	      }
	    }
	    if (status == IN_PROGRESS) {
	      if (read_result = GetOverlappedResult( hPipeRead, &gOverlapped,
						     &bytes_read, FALSE)) {
		bytes_read_so_far += bytes_read;
		ResetEvent(gOverlapped.hEvent);
	      } else
		switch (last_error = GetLastError()) {
		case ERROR_HANDLE_EOF: 
		case ERROR_BROKEN_PIPE: status = SUCCESS; break;
		}
	    }
	  }
      }
    }
    /* Close the ends of our pipe. Windows will not kill it
     *  until we dispose of all handles to it.
     */
    CloseHandle(hPipeRead);
  }
  if (INVALID_HANDLE_VALUE != hPipeWrite) {
    CloseHandle(hPipeWrite);
  }
  if (status == FAILURE)
    return(status);
  else {
    if (max_bytes <= 0)
      return(status);
    else if (bytes_read_so_far >= max_bytes)
      bytes_read_so_far = max_bytes - 1;
    string_from_pipe[bytes_read_so_far] = '\0';
    strncpy(buff, string_from_pipe, bytes_read_so_far);
    buff[bytes_read_so_far] = '\0';
    return (status);
  }
}
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#   else
long g2ext_unix_cmd_with_string_output_and_timeout_callback_mx(command, command_p, dir,
							       buff, timeout_in_ms, timeout_callback,
							       max_bytes)
     char    *command;
     int     command_p;
     char    *dir;
     char    *buff;
     long    timeout_in_ms;
     timeout_callback_fn timeout_callback;
     int max_bytes;
{				/* This is a stub function that should never be called. */
	return(0);
}
#   endif
#endif

#ifdef WIN32
/* TODO: merge this function with g2ext_spawn_command_directly --binghe */
int g2ext_spawn_command_directly_and_wait(command_string)
     char    *command_string;
{
    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO StartInfo;
    DWORD child_pid;
    DWORD creation_flags;
 
    /* We must pass this humongous STARTUPINFO struct to the
     *  CreateProcess() function. Most of the elements are
     *  ignored but must be initialized.
     */
    memset(&StartInfo, 0, sizeof(StartInfo));
    StartInfo.cb = sizeof(StartInfo);
 
    if (logging_to_file) 
      creation_flags = CREATE_NEW_PROCESS_GROUP | CREATE_NO_WINDOW;
    else
      creation_flags = CREATE_NEW_PROCESS_GROUP;

    if ( (CreateProcess(NULL, command_string, NULL, NULL, FALSE,
                        creation_flags, NULL, NULL,
                        &StartInfo, &ProcInfo)) == TRUE ) {

        /* The process id is passed back in the ProcInfo struct */
        child_pid = ProcInfo.dwProcessId;

        /* Since we will run concurrently with the new process,
         *  we release our handles. Note we MUST release our
         *  handles or waste system resources.
         */

        switch (WaitForSingleObject(ProcInfo.hProcess, WAIT_TIME_COMMAND)) {
            case WAIT_OBJECT_0:
                if(!GetExitCodeProcess(ProcInfo.hProcess, &child_pid)) {
                    child_pid = FAILURE;
                }
                break;
            default:
                child_pid = FAILURE;
                break;
        }
        CloseHandle(ProcInfo.hThread);
        CloseHandle(ProcInfo.hProcess);

        return ((int)child_pid);
    } else
        return ((int)FAILURE);
}
#endif

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_run_command_line(char *command_string)
 *
 *   Description:
 *     Runs the system() command and returns its status.
 *   Input Arguments:
 *     command_string: command to be executed by the system.
 *   Returns:
 *     return value: status returned by system()
 *   Notes:
 *     Adjunct to the G2 user file i/o facility.
 *     Under BSD Unix systems (sun4) apparently the system() call
 *        is implemented to obtain the process status by calling wait().  If a
 *        SIGCHLD handler is established (e.g. with establish_sigchld_handler())
 *        the handler "steals" the exit code and allows the process to
 *        terminate before system() obtains the status.  system() then returns
 *        -1 to indicate a non-existent process.  To circumvent this problem,
 *        the SIGCHLD handler can be set back to the default before and
 *        restored immediately after the system() call.
 *   Modifications:
 *     jh, 6/28/91.  No longer used in file i/o, but used in authorization
 *     mes, 6/10/94: Useful for special gsi programs such as platform.c
 *     mes, 12/1/94: Added sun4 #ifdefs (see Notes above).  jh
 *       told me that this has not been used for authorization for some time.
 *       Thus, it is currently called only by buildsh.c.
 *****************************************************************************/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(sun4)

int g2ext_run_command_line(command_string)
     char     *command_string;
{
    int      status;

    struct sigaction act, oldact;

    act.sa_handler = SIG_DFL;
    sigaction(SIGCHLD, &act, &oldact); /* Disable SIGCHLD handler; see Notes.*/

    status = system(command_string);

    sigaction(SIGCHLD, &oldact, NULL); /* Restore SIGCHLD handler. */

    return status;
}
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#elif defined(WIN32)

int g2ext_run_command_line(command_string)
     char     *command_string;
{
  int      status;

  status = g2ext_spawn_command_directly_and_wait(command_string);
  return status;
}

#else

int g2ext_run_command_line(command_string)
     char     *command_string;
{
  int      status;

  status = system(command_string);
  return status;
}
#endif

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_substatus_run_command_line(char *command_string)
 *
 *   Description:
 *     Runs the system() command and returns the status of the subprocess.
 *   Input Arguments:
 *     command_string: command to be executed by the system.
 *   Returns:
 *     return value:
 *       if a non-negative number: at least the low-order 8 bits of the return
 *         value of the subprocess, assuming the subprocess exits normally
 *         and returns a positive number.
 *       if an error occurs: -1,100,100 + errno (or zero if not known).
 *       if a signal terminates the subprocess abnormally:
 *          -100,000 + signal number.
 *       if the subprocess is stopped: -1,000,000 + the stop signal.
 *       all non-normal return cases:
 *          an error message is printed to standard output.
 *   Notes:
 *       Unix doesn't let you have more than 8 bits.  This may make
 *     use difficult for calling commands that return larger integers.  
 *     Likewise, it may be difficult to use commands that return -1.
 *       Similar to g2ext_substatus_run_command_line, but that is defined
 *     as returning the result of the system() function, whose result
 *     is defined differently from platform to platform.  This is intended
 *     provide the least common denominator of defined functionality, which
 *     turns out to be useful at present.  
 *       This should not be called by a running G2 except in very special
 *     situations, such as at startup time.
 *       All platforms should implement special protocol for determining
 *     if status works (is implemented, and can get a command interpreter): 
 *     status(NULL)  returns  non-zero  if it can; returns 0 if it cannot.
 *     However, my Sun4 prints out "-c: bad option(s)".  But we don't need
 *     this check because: Unix/VMS are guaranteed never to return 0, and 
 *     windows does return 0, but also returns a -1 status to indicate 
 *     it could not find a command interpreter, and this is the result we
 *     want anyway.  So, I've left out this check.
 *       Notes from Stevens, "Advanced Programming in the Unix Environment":
 *     "The system function should never be used from a set-user-ID or a 
 *     set-group-ID program" (p. 226) "[doing so] is a security hole and should
 *     never be done." (p. 224).  See the text for details and definitions.
 *     (But note that G2 is clearly not intended to be a set-user-ID program,
 *     so I don't think this has to be explicitly documented. -mhd)
 *
 *****************************************************************************/

/*0000000000000000000000000000 Mixed Ifdefs 000000000000000000000000000000000*/

long g2ext_substatus_run_command_line(command_string)
    char *command_string;
{
    int status, normal;

    status = g2ext_run_command_line(command_string);

    normal = 1;
#   if defined(unix)
        normal = WIFEXITED(status);
#   endif

#   if defined(WIN32)
        normal = (status != -1);
#   endif

    if (normal) {
#      if defined(unix)
           return(WEXITSTATUS(status));
#      else
           return(status);
#      endif
    }

    /* Error cases for unix and Windows (note: none for VMS)
     */
#   if defined(unix) || defined(WIN32)
        fprintf(stderr,
                "\n  Problem with command \"%s\"\n  nonnormal status: %d", 
	        command_string, status);
        if (status == -1) {
	    fprintf(stderr, "; errno: %d\n", errno);
	    perror("  G2");           /* print error message and newline */
	    return(-1100000 + errno); /* -1,100,000 + errno */
        }
#   endif  /* unix || WIN32 */

    /* Unix-only error cases
     */
#   if defined(unix)
        if (WIFSIGNALED(status)) {
	    fprintf(stderr, "; interrupt signal: %d\n", WTERMSIG(status));
	    return(-100000 + (WTERMSIG(status))); /*   -100,000 + signo */
        }

        if (WIFSTOPPED(status)) {
	    fprintf(stderr, "; stop signal: %d\n", WSTOPSIG(status));
	    return(-1000000 + WSTOPSIG(status));  /* -1,000,000 + signo */
        }
#   endif /* unix */
 /* Not sure that we ever get here, but better to return -1,100,000
  * than whatever happens to be on the stack. */
  return -1100000;
}
/*0000000000000000000000000000 Mixed Ifdefs 000000000000000000000000000000000*/



/*****************************************************************************
 * long g2ext_set_inherit_stdio_handles(long new_value)
 *
 *   Description:
 *     If this is NT, set the variable which decides whether or not to 
 *     inherit standard io handles from the parent process when spawning
 *     a new process.
 *   Input Arguments:
 *     new value for inherit_stdio_handles
 *   Returns:
 *     TRUE
 *   Notes:
 *     Meaningless on non-NT
 *   Modifications:
 *      4/8/98, jv, added
 *****************************************************************************/
#ifdef WIN32
long g2ext_set_inherit_stdio_handles(new_value)
    long new_value;
{
    inherit_stdio_handles = (BOOL) new_value;
    return TRUE;
}
#else
long g2ext_set_inherit_stdio_handles(new_value)
    long new_value;
{
    return TRUE;
}
#endif



/*****************************************************************************
 * double g2ext_spawn_command_directly(char *command_string)
 *
 *   Description:
 *     Runs command_string as a detached process without invoking a "shell".
 *     Arguments, possibly quoted, are passed directly without shell
 *     interpretation.
 *   Input Arguments:
 *     command_string:  command which is to be spawned
 *   Returns:
 *     return value: process id or an error status
 *   Notes:
 *     In the POSIX version of this function, the command_string that is
 *       passed as an argument is parsed to create a null terminated list of
 *       arguments of the form char *argv[]. This is then used in execvp as
 *       arguments to spawn the process. The command_string is of the form
 *       "<command> <args>". Arguments in single or double quotes are
 *       taken literally as one agrument in the argv[] list that is formed. The
 *       process is spawned directly without invoking a "shell" and this
 *       is how it differs from g2ext_spawn_command_line_process. For further
 *       details on this function see the g2ext_spawn_command_line_process()
 *       Notes in the function header below.
 *     In POSIX, execvp requires an initial argument.  Thus, we check for the
 *       presence of an argument and return -1.0 if there isn't one.
 *     The VMS and NT calls to g2ext_spawn_command_line_process() make use
 *       of the code here.
 *     In the VMS version, there is apparantly no separate way of spawning a
 *       a process on the command line. So this version of the function
 *       remains the same as that for g2ext_spawn_command_line_process() and
 *       so the latter just calls this function.
 *     In the WIN32 version, the g2ext_spawn_command_directly prepends "cmd /c".
 *       to the command_string to invoke the shell interpreter and then calls
 *       this function with the modified command_string.
 *   Modifications:
 *     7/10/95, mpc: (from g2ext_spawn_command_line_process() below)
 *       In WIN32 version, changed the fdwCreate param of
 *       CreateProcess() from 0 to CREATE_NEW_PROCESS_GROUP, which tells
 *       Win32 to establish a process group for the spawned console and its
 *       (console app) children. This allows us to kill (console only) children
 *       of the commandline interpreter by feeding a CTRL+BREAK down in
 *       g2ext_kill_spawned_command_line().
 *****************************************************************************/

#ifdef POSIX
static long parse_command_arguments(command_string,argv,array2d)
    char *command_string;
    char *argv[MAX_ARGS];
    char array2d[MAX_ARGS][MAX_ARG_LEN];
{
    int i = 0;
    int argc = 0;
    char delimiter;
    char *arg, *cmdptr;

    argc = 0;
    cmdptr = command_string;

    /* For each argument in the string, copy it into successive entries
     * of argv[][].
     */
    for (argc = 0; *cmdptr != '\0' && argc < MAX_ARGS - 1; argc++ ) {
        argv[argc] = array2d[argc];
        arg = argv[argc];

        while (*cmdptr == ' ')       /* Skip leading blanks */
            cmdptr++;

        if (*cmdptr == '\0')         /* If end of command string, we're done */
            break;

        /* What comes next must be an argument.  For single and double-quoted
         * arguments, the contents are taken directly (to the next matching
         * quote).  Non-quoted arguments are assumed to be delimited by spaces.
         */
        if (*cmdptr == '"' || *cmdptr == '\'') {
            delimiter = *cmdptr;
            cmdptr++;                /* Skip past the quote */
        } else
            delimiter = ' ';

        for (i=0; *cmdptr != delimiter && *cmdptr != '\0'; cmdptr++) {

            /* We may need to skip to the end of the argument without
             * exceeding array bounds.  It's okay to fill the final arg
             * position multiple times, since it is filled with
             * '\0' below
             */
            arg[i] = *cmdptr;
            if (i < MAX_ARG_LEN - 1)
                i++;
        }
        arg[i] = '\0';
        if (*cmdptr == delimiter)    /* Skip the closing delimiter */
            cmdptr++;
    }

    argv[argc] = NULL;
    return argc;
}

double g2ext_spawn_command_directly(command_string)
     char    *command_string;
{
  int child_pid;
  int argc;
  char array2d[MAX_ARGS][MAX_ARG_LEN];
  char *argv[MAX_ARGS];

  argc = parse_command_arguments(command_string, argv, array2d);

  /* Check that indeed there is an argument; i.e., that command_str
   * is not empty.  If it is, return the conventional error value
   * of -1.0, which indicates that process spawning failed.
   */

  if (argc == 0)
    return -1.0;

  /* Note that the code below is nearly identical, except for execvp(),
   * to the code in g2ext_spawn_command_line_process() below.  Changes should
   * be maintained in both.
   */

  if ((child_pid = vfork()) == 0)  { /* child */
    setpgid(getpid(), getpid());   /* See notes. */
    execvp(argv[0], argv);
    _exit(1);    /* Should never be reached.  Return error if it is. */
 
  } else  { /* parent */
    /* The parent reads the status to allow a child to exit */
    waitpid((pid_t) -1, 0, WNOHANG);
 
  }
  return (double) child_pid;
}
#endif /* POSIX version of g2ext_spawn_command_directly*/
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(WIN32)
double g2ext_spawn_command_directly(command_string)
     char    *command_string;
{
    PROCESS_INFORMATION ProcInfo;
    STARTUPINFO StartInfo;
    DWORD child_pid;
    DWORD creation_flags;
 
    /* We must pass this humongous STARTUPINFO struct to the
     *  CreateProcess() function. Most of the elements are
     *  ignored but must be initialized.
     */
    memset(&StartInfo, 0, sizeof(StartInfo));
    StartInfo.cb = sizeof(StartInfo);
 
    if (logging_to_file) 
      creation_flags = CREATE_NEW_PROCESS_GROUP | CREATE_NO_WINDOW;
    else
      creation_flags = CREATE_NEW_PROCESS_GROUP;

    if ( (CreateProcess(NULL, command_string, NULL, NULL, FALSE,
                        creation_flags, NULL, NULL,
                        &StartInfo, &ProcInfo)) == TRUE ) {

        /* The process id is passed back in the ProcInfo struct */
        child_pid = ProcInfo.dwProcessId;
 
        /* Since we will run concurrently with the new process,
         *  we release our handles. Note we MUST release our
         *  handles or waste system resources.
         */
        CloseHandle(ProcInfo.hThread);
        CloseHandle(ProcInfo.hProcess);
        return ((double)child_pid);
    } else
        return ((double)FAILURE);
}
#endif
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * double g2ext_spawn_command_line_process(char *command_string)
 *
 *   Description:
 *     Spawns a shell (a command interpreter) to run the command.
 *   Input Arguments:
 *     command_string:  command which is to be spawned
 *   Returns:
 *     return value: the process id of the spawned command interpreter or
 *       an error value
 *   Notes:
 *     A major problem under NT and Windows95 is that processes spawned
 *        with "cmd /c" run in a subshell.  Under Windows95, the processes
 *        cannot be killed.  Under NT, only console (non-windowed)
 *        applications can be killed. g2ext_spawn_command_line_process() above
 *        allows all processes to be terminated.
 *     To use this properly on Unix systems, g2ext_establish_sigchld_handler()
 *        should be called initially.  This prevents child processes from
 *        remaining zombies after they exit.  The call to waitpid() here is
 *        an added precaution for cleaning up zombies.
 *     lifted from ac's file_io rpc package.
 *     In the POSIX version, setpgid(getpid(), getpid()) sets the group id
 *        of the forked process.  This is done in conjunction with
 *        g2ext_kill_spawned_command_line(), which uses kill(-pid) to signal
 *        all processes in the process group of the spawned command line.
 *        Because processes are spawned with "sh -c", all subprocesses started
 *        by the shell can be killed by g2ext_kill_spawned_command_line().
 *     g2ext_spawn_command_directly() (above) in the POSIX version is almost
 *        identical to the POSIX version of g2ext_spawn_command_line_process. The
 *        former differs from the latter in that it spawns the process on the
 *        command line as opposed to running the process in a "shell" i.e
 *        what this function does. Whenever a change is made to the POSIX
 *        version of this function, make sure to check g2ext_spawn_command_
 *        directly() (POSIX version) for any similar changes.
 *
 *   Modifications:
 *     ap 10/2/96:  Changed the function to call g2ext_spawn_command_directly()
 *        with "cmd /c" prepended.  Before g2ext_spawn_command_directly() was
 *        added, this function was identical to that in
 *        g2ext_spawn_command_directly(), except that "cmd /c" was prepended
 *        directly.
 *        The VMS versions now simply call g2ext_spawn_command_directly
 *        with command_string as the argument. All the process spawning
 *        for these 2 versions is handled in the g2ext_spawn_command_directly.
 *     mes 6/9/94:  Reinstated setpgid(getpid(), getpid()). See note above.
 *        Also changed the exit(1) after execlp() to _exit(1) as recommended
 *        by man pages and other sources.
 *     mes 6/7/94:  In the POSIX version, provided use of vfork() for platforms
 *        that can currently make use of it.  Removed the intervening
 *        call to setpgid(getpid(), getpid()), which is not clearly needed.
 *        Note that on many platforms the man pages warn that vfork() may be
 *        eliminated at any time.  fork() typically reserves enough swap space
 *        for the forked image then deallocates it after execlp(), while
 *        vfork() does not reserve the space.  Neither the RS6000 nor SGI
 *        provides vfork(); the former does not reserve swap while the latter
 *        does.  OSF provides vfork(), but it reserves swap space just as
 *        fork() does, indicating that the calls are identical.
 *     mpc 11/22/93:  Changed system calls to POSIX compliance. SYSV
 *        and BSD versions of setpgrp() replaced with setpgid(). SYSV
 *        wait3() and BSD waitpid() replaced with POSIX waitpid().
 *****************************************************************************/
#ifdef POSIX

double g2ext_spawn_command_line_process(command_string)
     char    *command_string;
{
    int     child_pid;

    /* Note that the code below is nearly identical, except for execlp(),
     * to the code in g2ext_spawn_command_directly() above.  Changes should
     * be maintained in both.
     */

        if ((child_pid = vfork()) == 0)  { /* child */
	    setpgid(getpid(), getpid());   /* See notes. */
	    execlp("/bin/sh", "sh", "-c", command_string, (char *) 0);
	    _exit(1);    /* Should never be reached.  Return error if it is. */

        } else  { /* parent */
             /* The parent reads the status to allow a child to exit */
	    waitpid((pid_t) -1, 0, WNOHANG);

        }
	return (double) child_pid;
} 
#endif /* POSIX version of g2ext_spawn_command_line_process */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#if defined(WIN32)
double g2ext_spawn_command_line_process(command_string)
     char    *command_string;
{
    const size_t command_string_len = strlen(command_string);
    const char * cmd_prefix = "cmd /c ";
    const size_t cmd_prefix_len = strlen(cmd_prefix);
    char * cmd_command = (char *)malloc(command_string_len + cmd_prefix_len + 1);
    double return_value;
    
    /* Since NT CreateProcess() cannot execute shell commands, 
     *  we prepend all commands with the "cmd /c" program,
     *  which is a one-shot command shell interpreter.
     */

    if(cmd_command == NULL)
	    return FAILURE;
    cmd_command[0] = '\0';
    strcat(cmd_command, cmd_prefix);
    strcat(cmd_command, command_string);
    return_value = g2ext_spawn_command_directly(cmd_command);
    free(cmd_command);
    return(return_value);
}
#endif
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*****************************************************************************
 * int kill_spawned_command_line(double pid)
 *
 *   Description:
 *     TBA
 *   Input Arguments:
 *     pid: process id of command to kill
 *   Returns:
 *     return value: SUCCESS or FAILURE
 *   Notes:
 *     lifted from ac's file_io rpc package.
 *     There is no valid value for NT.
 *   Modifications:
 *     7/10/95, mpc: In the WIN32 code, added the call to the Win32 API
 *        function GenerateConsoleCtrlEvent(), which feeds a CTRL+BREAK to the
 *        spawned command shell and its (console app) children, thus killing
 *        the command spawned via the shell.  Note this only kills console
 *        apps and commands and not windowed apps.
 *     jh 7/8/94:  Changed the return type of this function to long as part of 
 *       the project to ensure that foreign functions get the correct argument
 *       and return types.  For further details, see my note this date in 
 *       /bt/ab/rtl/c/gensym.h.
 *     jh 11/14/91:  Removed reference to CLI$_NORMAL in the following
 *       statement.  The documentation states "if a nonzero value is returned,
 *       then the system function is supported.  This seems to be all the
 *       error-checking we have.
 *     jh 11/9/91:  Changed kill_spawned_command_line to take a double instead
 *       of an int, because VMS process IDs are too large for fixnums inside
 *       G2.  A corresponding change was made in spawn_command_line_process.
 *****************************************************************************/

/*0000000000000000000000000000 Mixed Ifdefs 000000000000000000000000000000000*/

long g2ext_kill_spawned_command_line (pid)
     double      pid;
{
    int     local_pid;
    int     status = FAILURE;

    local_pid = (int) pid;


#   ifdef unix
       status = kill((-local_pid), SIGKILL);
#   endif

#   if defined(WIN32)
    {
	HANDLE ProcHandle;

	if ( (ProcHandle = 
	      OpenProcess(STANDARD_RIGHTS_REQUIRED | PROCESS_TERMINATE, 
			  FALSE, (DWORD)pid) ) != NULL) {
	    GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, (DWORD)pid);
	    if ( TerminateProcess( ProcHandle, 0 ) == TRUE )
		status = SUCCESS;
	    CloseHandle( ProcHandle );
	}
    }
#   endif

   return status;
}
/*0000000000000000000000000000 Mixed Ifdefs 000000000000000000000000000000000*/

/*****************************************************************************
 * int g2ext_process_exists(double pid)
 *
 *   Description:
 *     Checks for the existence of the process whose process id is pid
 *     and returns true or false appropriately.
 *
 *   G2 Input Arguments:
 *     double: The id of the process.
 *   G2 Return Values:
 *     1 if process exists
 *     0 if process doesn't exist
 *    -1 if an error occurred
 *   Notes:
 *       This is currently used by shipping products (jh, 10/11/94).
 *       Because some of the platforms may indicate that an error occurs, it
 *     would be useful to have a third return value for that case.
 *   Modifications:
 *****************************************************************************/

#if defined(WIN32)

int g2ext_process_exists(pid)
    double pid;
{
    HANDLE ProcHandle;
    int    ExitCode = 0;
    int    ret = 0;
    int    existence;

    ProcHandle = OpenProcess(STANDARD_RIGHTS_REQUIRED
                               | PROCESS_QUERY_INFORMATION, 
                             FALSE,
                             (DWORD) pid);

    /* Next we check for existence. Note that there are 2 indicators that
     * process doesn't exist.
     */
    if (ProcHandle == NULL) {
        existence = 0;
    } else if (GetExitCodeProcess(ProcHandle, &ExitCode)) { /*error if FALSE*/
        if  (ExitCode == STILL_ACTIVE)
            existence = 1;
        else
            existence = 0; /* process terminated; exit status is available */
    } else {
        existence = -1;
    }

    if (ProcHandle != NULL)
      CloseHandle(ProcHandle);
    return (existence);
}
#endif
/*111111111111111111111111111 Multiply Defined 111111111111111111111111111111*/

/*111111111111111111111111111 Multiply Defined 111111111111111111111111111111*/
#ifdef POSIX

int g2ext_process_exists(pid)
    double pid;
{
    int existence;
    int returnpid = pid, i = 0;

    /* Note: on some platforms, sigchld_handler is not called, so we have to
       check for result = pid to receive the initial status information on exit
       which should have been checked for there.  So we call it again in
       order to get the actual error (up to 3 times, per sigchld_handler.) 
         --yduJ, Feb 2006
       HQ-3860878 "g2-process-exists() returns true first time called" */

    while (returnpid == pid && i < 3) {
      returnpid = waitpid((pid_t) pid, NULL, WNOHANG);
      i++;
    }

    /* if it's STILL returning the pid after 3 tries, give up and assume it
       still exists. */

    if (returnpid != -1)
        existence = 1;
    else if (errno == ECHILD)
        existence = 0;
    else
        existence = -1;

    return (existence);
}
#endif /* POSIX */
/*111111111111111111111111111 Multiply Defined 111111111111111111111111111111*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Process Signal Management
 %
 % Description:
 %      These functions provide signal handling for POSIX process termination.
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
 * static void sigchld_handler()
 *
 *   Description:
 *     This is a handler for the POSIX SIGCHLD signal.  It is used to
 *     terminate zombie processes.
 *   Input Arguments: none
 *   Returns: none
 *   Notes: 
 *       The handler is installed by g2ext_establish_sigchld_handler().
 *       To allow the possibility of multiple terminating children,
 *     waitpid() is called up to three times in the handler.
 *       The global errno is saved and restored on exit because waitpid()
 *     affects it. This guarantees integrity of its prior value.
 *   Modifications:
 *****************************************************************************/
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/
#ifdef POSIX
static void sigchld_handler(int signum)
{
    int saved_errno;
    int i;

    /* Save and on return restore the global errno. See notes. */
    saved_errno = errno;

    /* The following for loop has an empty body. */
    for ( i=0; (i < 3) && ( waitpid((pid_t) -1, NULL, WNOHANG) > 0 ); i++);
    errno = saved_errno;
}
#endif /* POSIX */
/*111111111111111111111111 Conditionally Defined 1111111111111111111111111111*/

/*****************************************************************************
 * int g2ext_establish_sigchld_handler()
 *
 *   Description:
 *       Sets up the SIGCHLD signal handler on platforms that have the signal.
 *
 *   Input Arguments: none
 *   Return value:
 *       SUCCESS - if handler was successfully established
 *                 or if no handler is needed
 *       FAILURE - otherwise
 *   Notes: 
 *       When a child process terminates it becomes a zombie until its parent
 *     checks its exit status.  Because the child generates a SIGCHLD signal
 *     when exiting, a handler (sigchld_handler()) is provided to check the
 *     exit status (with waitpid()).
 *       The POSIX sigaction() is used to set up the signal handler, since it
 *     provides reliable signal handling.
 *       See Stevens's Advanced Programming in the UNIX Environment for a full
 *     discussion of details.
 *
 *   Modifications:
 *****************************************************************************/
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#ifdef POSIX

int g2ext_establish_sigchld_handler(void)
{
    struct sigaction act;

    act.sa_handler = sigchld_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NOCLDSTOP;  /* Don't signal if child merely stops. */

#   ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#   endif

    if (sigaction(SIGCHLD, &act, NULL) < 0)
        return FAILURE;
    else
        return SUCCESS;
    
}
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/
#else /* not POSIX */

int g2ext_establish_sigchld_handler(void)
{
    return SUCCESS;
}
#endif /* POSIX */
/*000000000000000000000000000 Multiply Defined 000000000000000000000000000000*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Unused Process Access
 %
 % Description:
 %      These functions are currently unused.  They were used in the past
 %      and are included here because they provide potential knowledge.
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


static void cprocess_message (const char *fmt, ...)
{
  va_list ap;
  char buffer[400];
  
  va_start(ap, fmt);
  vsprintf(buffer, fmt, ap);
  va_end(ap);
  sprintf(buffer+strlen(buffer),"\n");
  g2ext_write_string_to_console(buffer);
}

#if defined(unix)
#  define COPY_LIBRARIES 0
#else
#  define COPY_LIBRARIES 1
#endif

#define COPY_LIBRARY_BUFFER_SIZE 4096

static char *copy_library_file(library_name)
   char *library_name;
{
  static short number_of_libraries_mangled = 0;
  int len, dot_location;
  int numread, numwritten, cnt = 0;
  char *new_name = NULL;
  char list[COPY_LIBRARY_BUFFER_SIZE];
  char file_number[8];
  int file_number_length;
  char *extension;
  int extension_length;
  FILE *in = 0, *out = 0;

#if COPY_LIBRARIES != 0
  in = GFOPEN(library_name, "rb");
#endif
  if (in) {
    number_of_libraries_mangled++;
    if (number_of_libraries_mangled > 999)
      number_of_libraries_mangled = 0;
    sprintf(file_number,"%03d%03d",
	    (int) (((long) GETPID) % 100000), 
	    number_of_libraries_mangled);
    file_number_length = strlen(file_number);
    len = strlen(library_name);
    for (dot_location=len - 1; 
	 (dot_location>=0) && (library_name[dot_location] != '.'); 
	 dot_location--);
    extension = (dot_location>0) ? library_name + dot_location : DEFAULT_EXTENSION;
    extension_length = strlen(extension);
    new_name = (char *) malloc(len + file_number_length + extension_length + 1);
    if (dot_location>0)
      strncpy(new_name, library_name, dot_location);
    else
      strcpy(new_name, library_name);
    strcpy(new_name + dot_location, file_number);
    strcpy(new_name + dot_location + file_number_length, extension);

    cprocess_message("new name = %s", new_name);
    out = GFOPEN(new_name, "wb");
  }
  if (!out) {
    len = strlen(library_name);
    new_name = (char *) malloc(len + 1);
    strcpy(new_name, library_name);
    GFCLOSE(in);
    return new_name;
  }

  cprocess_message("opened %s for writing", new_name);
  while (!feof(in)) {
    numread = fread(list, sizeof(char), COPY_LIBRARY_BUFFER_SIZE, in);
    numwritten = fwrite(list, sizeof(char), numread, out);
    cnt += numread;
  }
  GFCLOSE(out);
  GFCLOSE(in);
  cprocess_message("finished writing %s", new_name);

  return new_name;
}

typedef struct _LOADED_LIBRARY {
    char *library_name;
    HANDLE_TYPE library_handle;
    char *loaded_from_name;
    struct _LOADED_LIBRARY *next;
} LOADED_LIBRARY;

static LOADED_LIBRARY *loaded_library_list = (LOADED_LIBRARY *) 0;

static void add_loaded_library(library_name, handle, loaded_from_name)
   char *library_name;
   HANDLE_TYPE handle;
   char *loaded_from_name;
{
  LOADED_LIBRARY *library;

  library = (LOADED_LIBRARY *) malloc(sizeof(LOADED_LIBRARY));
  library->library_name = (char *) malloc(strlen(library_name) + 1);
  strcpy(library->library_name, library_name);
  library->loaded_from_name = loaded_from_name;
  library->library_handle = handle;
  library->next = loaded_library_list;
  loaded_library_list = library;
  return;
}

static void remove_loaded_library(library_name)
   char *library_name;
{
  LOADED_LIBRARY *library, *previous_library;

  for (previous_library = 0, library = loaded_library_list; 
       library && 0 != strcmp(library_name, library->library_name);
       previous_library = library, library = library->next)
    ;
  if (library) {
    if (previous_library)
      previous_library->next = library->next;
    else
      loaded_library_list = library->next;
    DLCLOSE(library->library_handle);
    cprocess_message("Unloaded library %s.", library_name);
#if (COPY_LIBRARIES != 0) && !defined(unix)
    /* delete file library->loaded_from_name */
#endif
    free(library->library_name);
    free(library->loaded_from_name);
    free(library);
  }
}


#ifdef WIN32
char *gensym_dlerror ()
{
    char *error_message;

    error_message = (char *) malloc(15 * sizeof(char));
    sprintf(error_message, "err 0x%x", GetLastError());
    return error_message;
}
#endif

#if !(defined(__STDC__) || defined(_MSC_VER)) || defined(__hpux)
long g2ext_load_library(library_name,entry_name,entry_argument)
   char *library_name;
   char *entry_name;
   void **entry_argument;
{
  cprocess_message("Failed to open library %s.", library_name);

  return -1; /* Failure */
}
#else
long g2ext_load_library(library_name,entry_name,entry_argument)
   char *library_name;
   char *entry_name;
   void **entry_argument;
{
  HANDLE_TYPE handle;
  char *new_library_name;
  long (*entry_function)(void **);

  new_library_name = copy_library_file(library_name);
  handle = DLOPEN(new_library_name);
#if (COPY_LIBRARIES != 0) && defined(unix)
  unlink(new_library_name);
#endif
  if (!handle) {
    cprocess_message("Failed to open library %s.  Error was %s",
		     new_library_name, DLERROR);
    return -1; /* failure */
  }
  remove_loaded_library(library_name);
  add_loaded_library(library_name, handle, new_library_name);
  cprocess_message("Loaded library %s (%s).", new_library_name, library_name);
  entry_function = (long (*)(void **))DLSYM(handle, entry_name);
  if (entry_function == 0) {
    cprocess_message("Failed find function %s in library %s.",
		     entry_name,new_library_name);
    remove_loaded_library(library_name);
    return -1; /* failure */
  }
  if (0 == (*entry_function)(entry_argument)) {
    cprocess_message("Library %s cannot be loaded into this version of G2.",
		     new_library_name);
    remove_loaded_library(library_name);
    return -1; /* failure */
  }
  return 0; /* success */
}
#endif


long g2ext_show_function_address(fn)
  void *fn;
{
  return 0;
}


long g2ext_set_include_directory(directory)
  char *directory;
{
  return 0;
}


long g2ext_produce_shared_object (kb_filename, nfiles, object_suffix, dll_filename)
   char *kb_filename;
   long nfiles;
   char *object_suffix;
   char *dll_filename;
{
  return 0;
}
