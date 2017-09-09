/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      buildsh.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Mark Staknis, Hong Shao
 +
 + Description: This is a GSI program (the build shell) that runs on remote
 +              machines and allows processes to be started and controlled
 +              by g2.
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
 +      Multiply Defined    Function appears multiple times, each definition
 +                          for an #ifdef specified platform.
 +      Mixed Ifdefs        Single definition for function containing platform
 +                          specific code #ifdef's.
 +      Platform Specific   Defined only on a particular platform.
 +
 + File Organization:
 +   Section:      INCLUDE FILES and FORWARD DECLARATIONS
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Entry Point
 +      void gsi_set_up ()                 0000000
 +   Section:      FUNCTION GROUP - G2 RPC Functions
 +      rpc_force_gsi_exit()               1111111
 +      rpc_invoke_system()                1111111
 +      rpc_read_first_line()              1111111
 +      read_first_line()                  2222222 Mixed Ifdefs
 +      rpc_spawn_process()                1111111
 +      rpc_spawn_process_directly()       1111111
 +      set_current_environment()          2222222 Mixed Ifdefs
 +      rpc_kill_process()                 1111111
 +      rpc_process_exists()               1111111
 +      rpc_define_vms_symbol()            1111111 Mixed Ifdefs
 +      define_vms_symbol()                2222222 Platform Specific
 +   Section:      FUNCTION GROUP - GSI Toolkit Functions
 +      gsi*()...                          0000000
 +   
 + External Interface:
 +
 +        This module does not export an interface.  The only externally
 +      visible C functions are the standard GSI "Toolkit functions" such
 +      as gsi_initialize_context() that are invoked from the GSI kernel. 
 +      
 + External G2 Interface (functions invocable as G2 rpcs):
 +
 +      rpc_force_gsi_exit ()
 +         Cause this program to exit.  Should be "started", not "called",
 +         from g2, since it never returns anything.
 +
 +      rpc_invoke_system(dir:text, spinid:text, cmd:text)
 +         Sets working directory to dir, spin_id environment variable to 
 +         spinid, and invokes system() with cmd.  Waits for call to complete
 +         before returning.
 +
 +      rpc_read_first_line(dir:text, filename:text)
 +         Opens the named file in the given directory and reads and returns
 +         an integer status and the first line.  Status is 0 for success
 +         and -1 for failure.
 +
 +      rpc_spawn_process(dir:text, cmd:text)
 +         Spawns the command cmd after setting the working directory to dir.
 +         The process id of the command is returned as a double.  This does
 +         not wait for the process to terminate.
 +
 +      rpc_spawn_process_directly(dir:text, cmd:text)
 +         Spawns the command cmd directly (not in a shell) after setting the 
 +         working directory to dir. The process id of the command is returned 
 +         as a double.  This does not wait for the process to terminate.
 +
 +      rpc_kill_process(pid:double)
 +         Terminates the process whose process id is pid.  Returns status of
 +         termination command.
 +
 +      rpc_process_exists(pid:double)
 +         Checks for the existence of the process whose process id is pid
 +         and returns true or false appropriately.
 +
 +      rpc_define_vms_symbol(name:text,value:text)
 +         Under VMS, this makes a system call to set the global value of
 +         of symbol "name" to "value".  Under non-VMS systems this does
 +         nothing.  Returns the status of the set_symbol call or 1 (on
 +         non-VMS systems).
 +
 + Depends On:
 +      cprim.c
 +
 + Notes:
 +     This module is intended to be the minimal code needed to manage
 +   remote processes.  It should be platform independent as much possible.
 +   For platform dependent needs, libcprim should be used if possible.
 +
 + Modifications:
 +   usage:   All modifications to this file should be listed here, with most
 +            recent first. In general, modification comments should merely
 +            provide a reference to a detailed modification comment in the
 +            appropriate section/function header.
 +
 +      3/24/94 -- mes: Ported this to gsi40 from gsi32.
 +      9/17/94 -- mes: Brought this up to date with gsi32 9oct95 version.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES and FORWARD DECLARATIONS
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifdef win32            /* Needed by read_first_line() */
#  include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>      /* Needed by read_first_line() */
#include "gsi_main.h"

/* Forward references. */
static declare_gsi_rpc_local_fn(rpc_force_gsi_exit);
static declare_gsi_rpc_local_fn(rpc_invoke_system);
static declare_gsi_rpc_local_fn(rpc_read_first_line);
static declare_gsi_rpc_local_fn(rpc_spawn_process);
static declare_gsi_rpc_local_fn(rpc_spawn_process_directly);
static declare_gsi_rpc_local_fn(rpc_kill_process);
static declare_gsi_rpc_local_fn(rpc_process_exists);
static declare_gsi_rpc_local_fn(rpc_define_vms_symbol);

/* This file used to include cprim.h directly, but that is no longer possible due 
   to inability to mix and match ANSI and non ANSI mode compilations on certain
   platforms (we cannot compile translated code in ANSI mode yet).  Thus, the
   following declarations are to cprim functions (interestingly, not all of them
   are actually declared in cprim.h.)   -- yduJ, 1/8/02 */

extern long g2ext_kill_spawned_command_line();
extern int g2ext_establish_sigchld_handler();
extern int g2ext_run_command_line();
extern int g2ext_process_exists();
extern long g2ext_str_change_default_dir();

static void set_current_environment();
static int read_first_line();

double g2ext_spawn_command_line_process();
double g2ext_spawn_command_directly();

#ifdef vms
#  include <descrip.h>  /* Needed by define_vms_symbol() */
#endif

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

#define DECNET_OBJECT_NAME "buildsh_port"
#define TCPIP_PORT_NUMBER   2020

#define MAX_CMD_LENGTH 4096   /* For command buffers. */

#define MAX_READBUF_SIZE 256  /* For reading lines from files */

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
/* This section is currently empty. */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Entry Point
 %
 % Description:
 %     The gsi_set_up() function provides initialization.
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
 * void gsi_set_up()
 *
 *   Description:
 *       This is initialization entry point of GSI.  It sets up RPCs and a
 *     sigchld hander.
 *   Input Arguments: none
 *   Notes:
 *       Under GSI 3.2 this code resides in main().
 *       g2ext_establish_sigchld_handler() is called to allow spawned processes
 *     to terminate.
 *       The GSI_STRING_CHECK option is needed to prevent \'s from being
 *     escaped by ~'s.
 *
 *****************************************************************************/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/
 
void gsi_set_up ()
{

    if (g2ext_establish_sigchld_handler() < 0) {
         printf("Unable to establish SIGCHLD handler\n");
         exit(1);
    }

    gsi_set_option(GSI_STRING_CHECK);

    gsi_rpc_declare_local(rpc_force_gsi_exit,"RPC_FORCE_GSI_EXIT");
    gsi_rpc_declare_local(rpc_invoke_system,"RPC_INVOKE_SYSTEM");
    gsi_rpc_declare_local(rpc_read_first_line,"RPC_READ_FIRST_LINE");
    gsi_rpc_declare_local(rpc_spawn_process,"RPC_SPAWN_PROCESS");
    gsi_rpc_declare_local(rpc_spawn_process_directly,
                          "RPC_SPAWN_PROCESS_DIRECTLY");
    gsi_rpc_declare_local(rpc_kill_process,"RPC_KILL_PROCESS");
    gsi_rpc_declare_local(rpc_process_exists,"RPC_PROCESS_EXISTS");
    gsi_rpc_declare_local(rpc_define_vms_symbol,"RPC_DEFINE_VMS_SYMBOL");
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - G2 RPC Functions
 %
 % Description:
 %     The functions in this section are invoked as rpc's from g2.  They
 %   are "registered" above in main().
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
 * void rpc_force_gsi_exit (item_array, count, call_index)
 *
 *   Description:
 *     Causes program to exit.
 *   G2 Input Arguments: none
 *   G2 Return Values: none
 *   Notes:
 *       This should also be invoked by "start" rather than "call", since it
 *     doesn't return anything.
 *       This is the standard rpc force_gsi_exit() found in internal gsi
 *     applications.
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_force_gsi_exit(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    gsi_int   call_index;
{
    printf("In rpc_force_gsi_exit(), exiting\n");
    exit(0);
}

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * void rpc_invoke_system(item_array, count, call_index)
 *
 *   Description:
 *     In the specified directory, invokes system() with the command passed as
 *       a string.  If the directory string is empty, the current directory
 *       is used.  The SPIN_ID variable is first set, either by prefixing
 *       it to the command (non-VMS) or setting it with a system call (VMS).
 *       Does not return until system() call is complete.
 *   G2 Input Arguments:
 *     text0: the working directory in which to execute the command
 *     text1: the spinid for the command
 *     text2: the command string to be executed
 *   G2 Return Values:
 *     integer: status returned by system() command or negative error value
 *       returned if change-directory command fails.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_invoke_system(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    static char last_spinid[64] = "###"; /* Initial value is never matched. */
    int status;
    char *cwd;
    char command[MAX_CMD_LENGTH];

    printf("in rpc_invoke_system()\n");

    /* If working directory string is non-empty, change to it.  */
    cwd = str_of(item_array[0]);
    if (strlen(cwd) > 0)
        status = g2ext_str_change_default_dir(cwd);
    else
        status = 0;      /* Set status to an acceptable value. */

    /* Either set the new spin_id in the environment (VMS) or prepend to the
     * command to set the spin_id.
     */
    strcpy (command, str_of(item_array[2]));         /* the command */
    set_current_environment (str_of(item_array[1]),  /* the environment vars */
                        command);

    printf("invoking g2ext_run_command_line with %s\n", command); 

    if (status >= 0)
        status = g2ext_run_command_line(command);

    printf("after rpc_invoke_system() with status %d\n", status);

    set_int(item_array[0],status);
    gsi_rpc_return_values(item_array,1,call_index,current_context);
}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * gsi_int rpc_read_first_line(arg_list, count, call_index)
 *
 *   Description:
 *     In the specified directory, opens and reads the first line of the
 *       named file.  If the directory is the empty string, use the current
 *       directory.
 *   G2 Input Arguments:
 *     text0: the directory in which the file resides
 *     text1: the file name
 *   G2 Return Values:
 *     integer: O if the call succeeded and -1 if not
 *     string:  the first line of the file
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_read_first_line(item_array, count, call_index)
    gsi_item    item_array[];
    gsi_int     count;
    call_identifier_type call_index;
{
    int status;
    char *cwd;
    char buf[MAX_READBUF_SIZE];

    printf("in rpc_read_first_line()\n");

    buf[0] = '\0';   /* Set return buffer empty initially. */

    /* If working directory string is non-empty, change to it. */
    cwd = str_of(item_array[0]);
    if (strlen(cwd) > 0)
        status = g2ext_str_change_default_dir(cwd);
    else
        status = 0;      /* Set status to an acceptable value. */

    if (status >= 0)
        status = read_first_line(str_of(item_array[1]), buf);

    printf("after rpc_read_first_line() with status %d\n", status);

    set_int(item_array[0],status);
    set_str(item_array[1],buf);
    gsi_rpc_return_values(item_array,2,call_index,current_context);

}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/****************************************************************************
 * int read_first_line (char* filename, char* buffer) 
 *
 *   Description:
 *       Opens the named file in the current directory, reads the first line,
 *     and returns it.
 *   Input arguments:
 *     filename: the name of the file to open
 *     buffer: a buffer of length MAX_READBUF_SIZE
 *   Return values:
 *     0 if successful, -1 if an error occurred
 *     buffer: the first line of the file
 *   Notes:
 *       Under VMS, the file is opened in shareable mode to allow maximum
 *     access to other processes.
 *       Under NT, only a single process can access a file.  Thus, conflicts
 *     are a real possibility. 
 *   Modifications:
 *****************************************************************************/

/*2222222222222222222222222222 Mixed Ifdefs 222222222222222222222222222222222*/

static int read_first_line (filename, buffer)
    char *filename;
    char *buffer;
{
    int last_index;
    FILE *fp;

    fp = fopen(filename, "r"
#         ifdef vms
              ,"shr=get,put,upd,del"  /* optional arg allows multiple access */
#         endif
         );
    if (fp == (FILE *)NULL) {
        printf("in read_first_line(): can't open file %s: errno is %d\n",
                  filename, errno);
        return(-1);
    }

    /* fgets() reads up to and including the first linefeed. */
    fgets(buffer, MAX_READBUF_SIZE, fp);
    fclose(fp);

    if (buffer == (char *)NULL) {
        printf("in read_first_line(): fgets() was unable to read from %s\n",
                  filename);
        return(-1);
    }

    /* Replace a final linefeed with a null terminator. */
    last_index = strlen(buffer) - 1;
    if (last_index >= MAX_READBUF_SIZE)
        buffer[MAX_READBUF_SIZE-1] = '\0';
    else if (last_index >= 0 && buffer[last_index]=='\n')
        buffer[last_index] = '\0';

    return(0);
}
/*2222222222222222222222222222 Mixed Ifdefs 222222222222222222222222222222222*/

/*****************************************************************************
 * void rpc_spawn_process(item_array, count, call_index)
 *
 *   Description:
 *     In the specified directory, spawns the process named by the input 
 *       string.  If the directory string is empty, the current directory
 *       is used.  The SPIN_ID variable is first set, either by prefixing
 *       it to the command (non-VMS) or setting it with a system call (VMS).
 *   G2 Input Arguments:
 *     text0: the working directory in which to execute the command
 *     text1: the spinid for the command
 *     text2: the command to be executed
 *   G2 Return Values:
 *     double: The process id of the spawned process or an error value. Error
 *       values are negative.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_spawn_process(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    double pid;
    char *cwd;
    int status;
    char command[MAX_CMD_LENGTH];

    printf("in rpc_spawn_process()\n");

    /* If working directory string is non-empty, change to it. */
    cwd = str_of(item_array[0]);
    if (strlen(cwd) > 0)
        status = g2ext_str_change_default_dir(cwd);
    else
        status = 0;      /* Set status to an acceptable value. */

    /* Either set the new spin_id in the environment (VMS) or prepend to the
     * command to set the spin_id.
     */
    strcpy (command, str_of(item_array[2]));        /* The command. */
    set_current_environment (str_of(item_array[1]), /* The environment vars. */
                        command);

    if (status < 0) {     /* If change-directory command failed ... */
        pid = status;     /* Use pid to return the error value. */
        printf("call to g2ext_str_change_default_dir failed; status %d\n",                      status);
    } else {
        printf("invoking g2ext_spawn_command_line_process with %s\n", command);
        pid = g2ext_spawn_command_line_process(command);
        printf("g2ext_spawn_command_line_process returned %d\n", (long)pid);
    }

    set_flt(item_array[0], pid);
    gsi_rpc_return_values(item_array,1,call_index,current_context);
}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * gsi_int rpc_spawn_process_directly(arg_list, count, call_index)
 *
 *   Description:
 *     In the specified directory, spawns the process directly (not in a 
 *       detached shell) named by the input string.  If the directory string 
 *       is empty, the current directory is used.
 *   G2 Input Arguments:
 *     text0: the working directory in which to execute the command
 *     text1: the command to be executed
 *   G2 Return Values:
 *     double: The process id of the spawned process or an error value. Error
 *       values are negative.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_spawn_process_directly(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    double pid;
    char *cwd;
    int status;
    char command[MAX_CMD_LENGTH];

    printf("in rpc_spawn_process_directly()\n");

    /* If working directory string is non-empty, change to it. */
    cwd = str_of(item_array[0]);
    if (strlen(cwd) > 0)
        status = g2ext_str_change_default_dir(cwd);
    else
        status = 0;      /* Set status to an acceptable value. */

    strcpy (command, str_of(item_array[1]));      /* The command. */

    if (status < 0) {     /* If change-directory command failed ... */
        pid = status;     /* Use pid to return the error value. */
        printf("call to g2ext_str_change_default_dir failed; status %d\n",                      status);
    } else {
        printf("invoking g2ext_spawn_command_directly  with %s\n", command);
        pid = g2ext_spawn_command_directly(command);
        printf("g2ext_spawn_command_directly returned %d\n", (long)pid);
    }

    set_flt(item_array[0], pid);
    gsi_rpc_return_values(item_array,1,call_index,current_context);
}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/****************************************************************************
 * void set_current_environment(char* environment_vars_string, char* command) 
 *
 *   Description:
 *       Either set the new environment variables in the environment (VMS) or 
 *     prepend to the command to set them. The environment variables are set 
 *     only if they are non-null.
 *   G2 Input Arguments:
 *     environment_vars_string: String containing pairs of environment variable
 *       followed by its value.
 *     command: The command to be executed.
 *   G2 Return Values:
 *     command:  For non-VMS, prepended with appropriate string to set 
 *       the environment.
 *   Notes:
 *       The previous environment_vars_string is saved under VMS to determine
 *     whether the environment variables need to be redefined.
 *     Beware of MSWindows.  In a command line of form
 *         set SPIN_ID=ab& \bt\%SPIN_ID%\g2\test
 *     %SPIN_ID% is evaluated BEFORE the line is processed, so the setting
 *     of SPIN_ID has no effect on the line.  In addition, no space should
 *     be put between the SPIN_ID value and the & or it will be treated
 *     as part of the variable value.
 *   Modifications:
 *****************************************************************************/

/*2222222222222222222222222222 Mixed Ifdefs 222222222222222222222222222222222*/

static void set_current_environment (environment_vars_string, command)
    char *environment_vars_string, *command;
{
    /* For VMS efficiency. */
    static char previous_environment_vars_string[MAX_CMD_LENGTH] = "---";
    char *token;
    char variable[MAX_CMD_LENGTH], value[MAX_CMD_LENGTH];
    char tmpbuf[MAX_CMD_LENGTH], tmpstring[MAX_CMD_LENGTH];

    /* If the environment_vars_string is empty, do nothing. */
    if ( strlen(environment_vars_string) == 0 )
        return;

    /*  Under VMS there is no need to set the environment variables if 
     *  they haven't changed.
     */
#   ifdef vms
        if (!strcmp(previous_environment_vars_string, environment_vars_string))
            return;
        else
            /* Save it for next invocation. */
            strcpy(previous_environment_vars_string, environment_vars_string);
#   endif

    strcpy (tmpbuf, (char *) "");
    token = strtok(environment_vars_string, (char *)" ");
    while (token) {
       strcpy(variable, token);
       token = strtok(NULL, (char *)" ");
       if (!token) {
           printf ("No specified value for environment variable %s\n", 
                    variable);
           break;
       }
       strcpy(value, token);

#      ifdef vms
           define_vms_symbol(variable, value);
#      else /* not vms */
#          if defined(WIN32) || defined(__WATCOMC__)  /* i.e., Windows */
               sprintf(tmpstring, "set %s=%s&", variable, value);
               strcat(tmpbuf, tmpstring);
#          else  /* not VMS or Windows, so assume it's Unix Bourne shell. */
               sprintf(tmpstring, "%s=%s; export %s;", variable, value, variable);
               strcat(tmpbuf, tmpstring);
#          endif
#      endif
       token = strtok(NULL, (char*)" ");
    }
#   ifdef vms
        return;
#   else
        strcat(tmpbuf, command);
        strcpy(command, tmpbuf);
#   endif
}
/*2222222222222222222222222222 Mixed Ifdefs 222222222222222222222222222222222*/

/*****************************************************************************
 * void rpc_kill_process(item_array, count, call_index)
 *
 *   Description:
 *     Terminates the process whose process id is given.
 *   G2 Input Arguments:
 *     double: The id of the process to be terminated.
 *   G2 Return Values:
 *     status returned by the kill command (see g2ext_kill_spawned_command_line())
 *   Notes:
 *   Modifications:
 *****************************************************************************/
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_kill_process(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    long status;

    printf("in rpc_kill_process()\n");

    status = g2ext_kill_spawned_command_line(flt_of(item_array[0]));
    printf("after g2ext_kill_spawned_command_line with status %d\n", status);

    set_int(item_array[0],status);
    gsi_rpc_return_values(item_array,1,call_index,current_context);
}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * void rpc_process_exists(item_array, count, call_index)
 *
 *   Description:
 +     Checks for the existence of the process whose process id is pid
 +     and returns true or false appropriately.
 *   G2 Input Arguments:
 *     double: The id of the process.
 *   G2 Return Values:
 *     1 if process exists
 *     0 if process doesn't exist
 *    -1 if an error occurred
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void rpc_process_exists(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    int status;

    printf("in rpc_process_exists()\n");

    status = g2ext_process_exists(flt_of(item_array[0]));
    printf("after g2ext_process_exists with status %d\n", status);

    set_int(item_array[0],status);
    gsi_rpc_return_values(item_array,1,call_index,current_context);
}
/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/****************************************************************************
 * void rpc_define_vms_symbol(item_array, count, call_index)
 *
 *   Description: 
 *     GSI interface to define a VMS symbol to have the given value. 
 *   G2 Input Arguments:
 *     text1: The symbol to be defined.
 *     text2: The value the symbol is to be given.
 *   G2 Return Values:
 *     The return value of the VMS lib$set_symbol call,
 *     or 0 on non-VMS systems.
 *   Notes:
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111 Mixed Ifdefs 1111111111111111111111111111111*/

static void rpc_define_vms_symbol(item_array, count, call_index)
    gsi_item  item_array[];
    gsi_int   count;
    call_identifier_type   call_index;
{
    int status;

    printf("in rpc_define_vms_symbol()\n");

#   ifdef vms
        status = define_vms_symbol(str_of(item_array[0]), str_of(item_array[1]));
#   else
        status = 1;
#   endif

    set_int(item_array[0],status);
    gsi_rpc_return_values(item_array,1,call_index,current_context);

    printf("after rpc_define_vms_symbol with status %d\n", status);
}
/*111111111111111111111111111111 Mixed Ifdefs 1111111111111111111111111111111*/

/****************************************************************************
 * int define_vms_symbol(char* name, char* definition)
 *
 *   Description:
 *     Uses a system call to define a symbol to have the given value. 
 *   G2 Input Arguments:
 *     name: The symbol to be defined.
 *     definition: The value the symbol is to be given.
 *   G2 Return Values:
 *     The return value of the lib$set_symbol() call.
 *   Notes:
 *       The code here is taken with some modifications from a VMS tech
 *     support example sent to show how to do this.  Passing &2 is indeed
 *     funky.
 *   Modifications:
 *****************************************************************************/

/*2222222222222222222222222222 Platform Specific 2222222222222222222222222222*/
#ifdef vms

static int define_vms_symbol(name, definition)
    char *name, *definition;
{
    int status;
    $DESCRIPTOR(symbol, name);
    $DESCRIPTOR(value, definition);

    symbol.dsc$w_length = strlen(name);
    value.dsc$w_length = strlen(definition);
    status = lib$set_symbol(&symbol, &value, &2);

    return(status);
}
#endif
/*2222222222222222222222222222 Platform Specific 2222222222222222222222222222*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - GSI Toolkit Functions
 %
 % Description:
 %       The functions in this section are copied directly from skeleton.c
 %     and provide default behavior.
 %
 % Notes:
 %
 % Modifications:
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*000000000000000000000000000000000000000000000000000000000000000000000000000*/

gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER);
}

gsi_int gsi_initialize_context(remote_process_init_string, length)
    char    *remote_process_init_string;
    gsi_int  length;
{
    printf("%s\n",remote_process_init_string);
    return (GSI_ACCEPT);
}

void gsi_receive_registration(item_registration)
    gsi_registration item_registration;
{
    printf ("gsi_receive_registration in context %d\n",gsi_current_context());
}

void gsi_get_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    printf ("gsi_get_data in context %d\n",gsi_current_context());
}

void gsi_set_data(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    printf ("gsi_set_data in context %d\n",gsi_current_context());
}

void gsi_pause_context()
{
    printf ("gsi_pause_context in context %d\n",gsi_current_context());
}

void gsi_resume_context()
{
    printf ("gsi_resume_context in context %d\n",gsi_current_context());
}

void gsi_shutdown_context()
{}

void gsi_g2_poll()
{
    printf ("\ngsi_g2_poll in context %d\n",gsi_current_context());
}

void gsi_receive_deregistrations(registered_items, count)
    gsi_registered_item  registered_items[];
    gsi_int              count;
{
    printf ("gsi_receive_deregistrations in context %d\n",gsi_current_context());
}

void gsi_receive_message(message, length)
    char     *message;
    gsi_int   length;
{
    printf ("gsi_receive_message in context %d\n",gsi_current_context());
    printf ("G2 says:%s\n",message);
}
/*000000000000000000000000000000000000000000000000000000000000000000000000000*/
