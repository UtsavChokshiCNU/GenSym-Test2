/* $Id: spawn.c,v 1.10 2001-09-28 21:15:53 yduj Exp $ */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "codes.h"

#define PERROR_EXIT(message)  {                                  \
  fprintf(stderr, "(%s) %s at \"%s\":%d: %s\n",                  \
      executable, message, __FILE__, __LINE__, strerror(errno)); \
  abort(); }

extern char *executable;

static char *likely_tar_locations[] = { "/usr/bin/tar",
					"/sbin/tar",
					"/usr/sbin/tar",
					"/bin/tar",
					NULL };

/* ARGSUSED */
static void sigchld_handler(int signum)
{
#ifdef DONT_BE_QUIET
  printf ("child exiting\n");
  fflush (stdout);
#endif
  return;
}

/*
 * Setup SIGCHLD handler so we won't create a zombie child process.
 */ 
void establish_sigchld_handler()
{
  struct sigaction act;

  sigemptyset(&act.sa_mask);
  act.sa_handler = sigchld_handler;
  act.sa_flags = SA_NOCLDSTOP;  /* Don't signal if child merely stops. */

#ifdef SA_RESTART
  act.sa_flags |= SA_RESTART;
#endif

  if (sigaction(SIGCHLD, &act, NULL))
    PERROR_EXIT("sigaction");

  return;
}

/*
 * Find tar(1) in strangest way possible so that we have some hope that they
 * haven't just substituted the tar on their path with cat.
 */
int find_tar_executable(char **str)
{
  struct stat sb;
  char **sptr = likely_tar_locations;

  do {
#ifdef DONT_BE_QUIET
    printf("checking %s\n", *sptr);
#endif
    if (!stat(*sptr, &sb)) {
      *str = strdup(*sptr);
#ifdef DONT_BE_QUIET      
      fprintf(stderr, "we'll be using %s today\n", *str);
#endif
      return 0;
    }
  } while (*sptr++ != NULL);

  return NO_TAR_EXECUTABLE_FOUND;
}

/*
 * Print a "heartbeat" until the child returns.
 */
int wait_for_child_with_heartbeat()
{
  pid_t pid;

  do {
    pid = waitpid(-1, NULL, WNOHANG);
    if (pid == -1) {
      if (errno == ECHILD)
	/* HQ-4081297: sometimes sparcsol gets ECHILD instead of 0; we don't
           know why.  So, we assume if we get ECHILD, that our child has exited
           and we are done and ready to continue with installation. */
	return SUCCESS;
      else
	return WAITPID_FAILURE;
    }
    putchar('*');
    fflush(stdout);
    sleep(1);
  } while (pid != 0);

  putchar('\n');

  return SUCCESS;
}

/*
 * Fork and prepare child to run tar taking input from parent.  See
 * W. Richard Stevens "Advanced Programming in the Unix Environment",
 * chapter 14 for more information.
 */
FILE *open_output_pipe_for_command(char *command, char *argv[], char *path)
{
  int fd[2], devnull;
  pid_t pid;
      
  if (pipe(fd) == -1)
    return NULL;
    
  switch ((pid = fork()))
  {
  case -1:
    PERROR_EXIT("fork");

  case 0:			/* child process */
    close(fd[1]);

#ifndef DONT_BE_QUIET
    close(fileno(stderr));
    close(fileno(stdout));
#endif

    if ((devnull = open("/dev/null", O_WRONLY)) == NULL)
      PERROR_EXIT("open");

#ifndef DONT_BE_QUIET
    dup2(devnull, fileno(stdout));
    dup2(devnull, fileno(stderr));
#endif

    if (fd[0] != fileno(stdin)) {
      dup2(fd[0], fileno(stdin));
      close(fd[0]);
    }
        
    if (path)
      if (chdir(path))
	PERROR_EXIT("chdir");

    if (execve(command, argv, NULL) == -1) 
      PERROR_EXIT("execve");

    close(devnull);
    exit(0);

  default:			/* parent process */
    close(fd[0]);
    return fdopen(fd[1], "w");
  }
}
