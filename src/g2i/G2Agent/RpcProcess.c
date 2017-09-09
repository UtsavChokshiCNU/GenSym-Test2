/***************************************************************************
 *
 *		ProcessRpcsFuncs.c
 *
 *			Contains the Process GSI RPC functions. 
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/

#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>
#include	<string.h>

#include	<sys/types.h>
#include	<sys/stat.h>
#if !defined(WIN32)
#include	<sys/wait.h> 
#endif

#include	"G2Agent.h"



/*-------------------------------------------------------------------------*
 *
 *	Exit bridge
 *
 *-------------------------------------------------------------------------*/

void rpc_exit(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_int i;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_exit().\n");

    for (i = 1 ; i < MAX_FPTRS ; i++) {
        if (f_ptrs[i] != FILE_FREE)
			fclose(f_ptrs[i]);
	}

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_exit().\n\n");

    exit(0);
}


/*-------------------------------------------------------------------------*
 *
 *	Ping bridge
 *
 *-------------------------------------------------------------------------*/

void rpc_ping(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_ping().\n");

    set_log(local_gsi_itemP[0], GSI_TRUE);
    gsi_rpc_return_values(local_gsi_itemP, 1, call_index,  current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_ping().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Exectute the command sent from g2 and return the Process ID.
 *
 *-------------------------------------------------------------------------*/

#if defined(WIN32)

double spawn_command(gsi_char *command_string)
{
	PROCESS_INFORMATION ProcInfo;
    STARTUPINFO StartInfo;
    DWORD child_pid;
    DWORD creation_flags;
	BOOL inherit_stdio_handles = TRUE;
	BOOL logging_to_file = TRUE;
 
    /* We must pass this humongous STARTUPINFO struct to the
     *  CreateProcess() function. Most of the elements are
     *  ignored but must be initialized.
     */
    memset(&StartInfo, 0, sizeof(StartInfo));
    StartInfo.cb = sizeof(StartInfo);
 
    if (inherit_stdio_handles) {

		/* These members are important. By using USESTDHANDLES flag,
		 *  we tell the child process to use as stdin/stdout/stderr
		 *  the handles we pass.
		 * Note here that the handles to the pipe we created must
		 *  have been created with security attribute "inherit"
		 *  set to true.
		 */
		StartInfo.dwFlags = STARTF_USESTDHANDLES;
		StartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		StartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		StartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    }

    if (logging_to_file) 
      creation_flags = CREATE_NEW_PROCESS_GROUP | CREATE_NO_WINDOW;
    else
      creation_flags = CREATE_NEW_PROCESS_GROUP;

    if ( (CreateProcess(NULL, command_string, NULL, NULL, TRUE,
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

        return ((double) -1.0);
}

#else

#define	MAX_ARGS	100
#define	MAX_ARG_LEN	100

static long parse_command_arguments(char *command_string,char *argv[MAX_ARGS],char array2d[MAX_ARGS][MAX_ARG_LEN])
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


double spawn_command(gsi_char *command_string)
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

#endif

void rpc_spawn_process (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	double		pid;
	gsi_char	*cmd;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_spawn_process().\n");

	// Dereference the command string sent from g2.
	cmd = str_of(item_array[0]);

#if defined(WIN32)
    _flushall();
#endif

	pid = spawn_command(cmd);

	log_with_timestamp(LOG_MODE_DEBUG, "Launched process (PID %g): %s\n", pid, cmd);

	set_flt (local_gsi_itemP[0], pid);
	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_spawn_process().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Kill a process given the Process ID
 *
 *-------------------------------------------------------------------------*/

void rpc_kill_process (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	double	dbl_pid;
	int		ret = GSI_FALSE;
#if defined(WIN32)
	DWORD	pid;
	HANDLE	ProcHandle;
#else
	pid_t	pid;
	int		n;
#endif

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_kill_process().\n");

    dbl_pid = flt_of(item_array[0]);

#if defined(WIN32)
	pid = (DWORD) dbl_pid;

	ProcHandle = OpenProcess((DWORD)(STANDARD_RIGHTS_REQUIRED | PROCESS_TERMINATE), FALSE, pid);

	if (ProcHandle != (HANDLE) NULL) {

	    GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, pid);

	    if ( TerminateProcess( ProcHandle, 0 ) == TRUE )
			ret = GSI_TRUE;

	    CloseHandle( ProcHandle );
    }
#else
	pid = (pid_t) dbl_pid;

	n = kill(pid, SIGKILL);
	if (n == 0) ret = GSI_TRUE;
#endif

	log_with_timestamp(LOG_MODE_DEBUG, "Killed process with PID %g: %d\n", dbl_pid, ret);

	set_log (local_gsi_itemP[0], ret);
	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_kill_process().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	Check if process exists given the Process ID
 *
 *-------------------------------------------------------------------------*/

void rpc_process_exists (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	double	dbl_pid;
	unsigned long int flags = 0;
    int    existence;
#if defined(WIN32)
	DWORD	pid;
    HANDLE ProcHandle;
    int    ExitCode = 0;
    int    ret = 0;
#else
	pid_t	pid, returnpid;
	int		i;
#endif

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_process_exists().\n");

    dbl_pid = flt_of(item_array[0]);

#if defined(WIN32)
	pid = (DWORD) dbl_pid;

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
#else
	pid = (pid_t) dbl_pid;

	returnpid = pid;
	i = 0;

    while (returnpid == pid && i < 3) {
      returnpid = waitpid(pid, NULL, WNOHANG);
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
#endif

	log_with_timestamp(LOG_MODE_DEBUG, "Check if process with PID %g exists: %d\n", dbl_pid, existence);

	set_int (local_gsi_itemP[0], existence);
	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_process_exists().\n\n");
}

