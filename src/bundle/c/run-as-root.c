/* $Id: run-as-root.c,v 1.3 2002-01-04 23:09:23 mhd Exp $ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pwd.h>
#include <syslog.h>

#define STREQ(s1, s2) ((strstr(s1, s2)) == s1)

/* The following records, in a tricky manner, the only legal initial substrings
 for a command: "chmod -R root:root", "chmod -R root.root", "chmod -R g-w".

 Note: the check we make is very senstive, i.e., it's completely sensitive to
 whitespace and letter case.

 Instead of having char * (i.e., string) constants, we do the tricky business so
 that a curious would-be user cannot run the strings command on the compiled
 version of this file to learn the acceptable commands. */

static long longstr1[] = { 'c', 'h', 'm', 'o', 'd', ' ', '-', 'R', ' ', 'r', 'o', 'o', 't', ':', 'r', 'o', 'o', 't' };
static long longstr2[] = { 'c', 'h', 'm', 'o', 'd', ' ', '-', 'R', ' ', 'r', 'o', 'o', 't', '.', 'r', 'o', 'o', 't' };
static long longstr3[] = { 'c', 'h', 'm', 'o', 'd', ' ', '-', 'R', ' ', 'g', '-', 'w' };

char *tricky_strdup(long *longstr, int length)
{
  char *str = malloc((length) + 1);
  int i;

  for (i = 0; i < length; i++)
    str[i] = (char)longstr[i];
  str[length] = '\0';
  return str;
}


int
main (int argc, char *argv[])
{  
  char *argp[] = { "sh", "-c", argv[1], NULL };
  struct passwd *pw = getpwuid(geteuid());

  if (argc != 2) {
    fprintf(stderr, "bad args, punt!\n");
    exit(-1);
  }


#ifdef NOT_YET
  { /* Make a log entry noting that we have run a command as root. */
    openlog("run-as-root", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "run-as-root: %s (%d) tried %s", pw->pw_name, pw->pw_uid, argp[2]);
    closelog();
  }
#endif

  if (!(STREQ(argp[2], tricky_strdup(longstr1, sizeof(longstr1)/sizeof(long)))
	|| STREQ(argp[2], tricky_strdup(longstr2, sizeof(longstr2)/sizeof(long)))
	|| STREQ(argp[2], tricky_strdup(longstr3, sizeof(longstr3)/sizeof(long))))) {
    fprintf(stderr, "forbidden command \"%s\", punt!\n", argp[2]);
    exit(-1);
  }

  if (setuid(0) == -1 || setgid(0) == -1)
    fprintf(stderr, "warning, can't change identity!\n");

  if (execv("/bin/sh", argp) == -1) {
    perror("execv");
    exit(-1);
  }

  return 0;
}

