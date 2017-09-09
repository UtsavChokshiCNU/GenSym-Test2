/*  This is used by build-check to find errors efficiently.
 *  Compile it with
 *    gcc -o get-c-warnings -O get-c-warnings.c
 */


#include <stdio.h>
#define TRUE 1
#define FALSE 0

char *
move_to_next_token(buffer)
char *buffer;
{
  char *p;

  p = buffer;
  while (isspace(*p)) ++p;
  return p;
}

int
line_is_abnormal(buffer)
char *buffer;
{
  if ((strncmp(buffer,"cc_log",6)) &&
      (strncmp(buffer,"cc ",3)) &&
      (strncmp(buffer,"cc-with ",7)) &&
      (strncmp(buffer,"purge",5)) &&
      (strncmp(buffer,"echo",4)) &&
      (strncmp(buffer,"ar ",3)) &&
      (strncmp(buffer,"ranlib ",6)) &&
      (strncmp(buffer,"misc_files",10)) &&
      (strncmp(buffer,"make -i",6)) &&
      !(strstr(buffer,"warning: statement not reached")) &&
      (strncmp(buffer,"(cd",3)))
    return TRUE;
  return FALSE;
}


process_file(fdin,fdout)
FILE *fdin,*fdout;
{
  char buffer[5000],*firstchar;

  while (fgets(buffer,sizeof(buffer),fdin) != (char *) NULL) {
    firstchar = move_to_next_token(buffer);
    if (line_is_abnormal(firstchar)) 
      fprintf(fdout,buffer);
  }
}

main(argc,argv)
int argc;
char **argv;
{
  char *logfile,warningsfile[100],*p;
  FILE *fdin,*fdout;

  while (--argc) {

    logfile = *++argv;
    if ((fdin = fopen(logfile,"r")) == (FILE *) NULL) {
      perror(logfile);
      exit(1);
    }

    p = (char *)strchr(logfile,'.');
    *p = '\0';
    sprintf(warningsfile,"%s-w.log",logfile);

    if ((fdout = fopen(warningsfile,"w")) == (FILE *) NULL) {
      perror(warningsfile);
      exit(1);
    }

    process_file(fdin,fdout);
  }
}



