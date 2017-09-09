/*  This is used by build-check to find errors efficiently.
 *  Compile it with
 *    gcc -o get-warnings -O get-warnings.c
 */

#include <stdio.h>
#define TRUE 1
#define FALSE 0

int error_on_current_line(line)
char *line;
{
  int i;

  for (i=0;i<strlen(line);++i) {
    if (line[i] == 'E') 
      if (!strncmp(&line[i],"Error:",6) ||
	  !strncmp(&line[i],"ERROR-TRAPPED",13))
	  return 1;
    }
  return 0;
}

int ignore_this_warning(fd,current_line,next_line)
FILE *fd;
char *current_line, *next_line;
{
  int ignore;

  if (!strncmp(current_line,"Warning:",8)) {
    if (fgets(next_line,200,fd) != (char *) NULL) {
      if (!strncmp(next_line,"  INLINE-FUNCALL",16) ||
	  !strncmp(next_line,"  INLINE-DOUBLE",15) ) {
	ignore = 1;
	while ((fgets(next_line,200,fd)) &&
	       strncmp(next_line,"Translating ",12));
      }
      else {
	ignore = 0;
      }
    }
  }
  return ignore;
}


char *record_all_translation_warnings_for_this_file(file_being_translated,line,fd,fd2)
char *file_being_translated,line[];
FILE *fd,*fd2;
{
  char previous_line[1024], current_line[100], *p2;
  char next_line[200];

  strcpy(current_line,line);

  while (1) {
    strcpy(previous_line,current_line);
    if (fgets(current_line,sizeof(current_line),fd)) {
      if (!strncmp(current_line,"Translating file",16))
	return current_line;
      else
	if (strncmp(current_line,"Translating ",12) &&
	    strncmp(current_line,";;;",3) &&
	    strncmp(current_line,"\n",1) ||
	    error_on_current_line(current_line)) {
	  if (!ignore_this_warning(fd,current_line,next_line)) {
	    fputs(file_being_translated,fd2);
	    fputs(previous_line,fd2);
	    fputs(current_line,fd2);
	    fputs(next_line,fd2);
	    while ((p2 = fgets(current_line,sizeof(current_line),fd)) &&
		   strncmp(current_line,"Translating ",12))
	      fputs(current_line,fd2);
	  }
	  else strcpy(current_line,next_line);
	}
    }
   else return (char *) NULL;
  }
}

char *record_all_compile_warnings_for_this_file(file_being_compiled,line,fd,fd2)
char *file_being_compiled,line[];
FILE *fd,*fd2;
{
  char previous_line[1024], current_line[100], *p2;

  strcpy(current_line,line);

  while (1) {
    strcpy(previous_line,current_line);
    if (fgets(current_line,sizeof(current_line),fd)) {
      if (!strncmp(current_line,"Compiling",9) ||
	  !strncmp(current_line,"Loading",7) ||
	  (!strncmp(current_line,"Translating file",16))) {
	if (!strncmp(previous_line,"Loading",7) &&
	    !strncmp(previous_line,"Compiling",9))
	  fgets(current_line,sizeof(current_line),fd);
	return current_line;
      } else if (!strncmp(current_line,";;; Warning:",12) ||
		 !strncmp(current_line,";;; Error:",10) ||
		 !strncmp(current_line,"ERROR-TRAPPED",13)) {
	fputs(file_being_compiled,fd2);
	fputs(previous_line,fd2);
	fputs(current_line,fd2);
	while ((p2 = fgets(current_line,sizeof(current_line),fd)) &&
	       strncmp(current_line,"Loading",7) &&
	       strncmp(current_line,"Compiling",9) &&
	       strncmp(current_line,";;; Writing",10) &&
	       strncmp(current_line,"\n",1))
	  fputs(current_line,fd2);
      }
    }
    else return (char *) NULL;
  }
}

void get_header_info(fd,fd2)
FILE *fd,*fd2;
{
  char line[1024];
  int i;

  /* read until Dribble file started */

/*  while (fgets(line,sizeof(line),fd) &&
 *	 strncmp(line,";;; Dribble file",16));
 */
  /* Get the first 3 lines of header information */
/*  for (i=0;i<3;++i) {
 *    if (fgets(line,sizeof(line),fd))
 *      fputs(line,fd2);
 *    else {
 *      fprintf(stderr,"Premature EOF\n");
 *      exit(1);
 *    }
 *  }
 */

  /* read until the compile is starting */

  while (fgets(line,sizeof(line),fd) &&
	 strncmp(line,"Compiling",9));

  /* Get the first 3 lines of header information */
  fputs(line,fd2);
  for (i=0;i<2;++i) {
    if (fgets(line,sizeof(line),fd))
      fputs(line,fd2);
    else {
      fprintf(stderr,"Premature EOF\n");
      exit(1);
    }
  }


  fputs("\n________________________________\n\n",fd2);
}

main(argc,argv)
int argc;
char *argv[];
{
  FILE *fd,*fd2;
  char logfile[100], warningsfile[100],*p,*res;
  char line[1024], file_being_translated[1024], file_being_compiled[1024];
  int pass = 0;
  int get_new_line = TRUE;

  if (argc < 2) {
    fprintf(stderr,"usage: %s filename\n",argv[0]);
    exit(1);
  }

  strcpy(logfile,argv[1]);
  p = (char *)strchr(logfile,'.');
  *p = '\0';
  sprintf(warningsfile,"%s-w.log",logfile);

  if ((fd = fopen(argv[1],"r")) == (FILE *) NULL) {
    fprintf(stderr,"error opening %s\n",argv[1]);
    exit(1);
  }
  if ((fd2 = fopen(warningsfile,"w")) == (FILE *) NULL) {
    fprintf(stderr,"error opening %s\n",warningsfile);
    exit(1);
  }
  get_header_info(fd,fd2);

  while (1) {
    if (get_new_line) {
      p = fgets(line,sizeof(line),fd);
      if (p == (char *) NULL) break;
    }
    else
      strcpy(line,p);

    if (!strncmp(line,"Translating file",16)) {
      sprintf(file_being_translated,"\n%s",line);
      p = record_all_translation_warnings_for_this_file(file_being_translated,line,fd,fd2);
    } else if (!strncmp(line,"Compiling",9) || !strncmp(line,"Loading",7) || !strncmp(line,"Updating",8)) {
      sprintf(file_being_compiled,"\n%s",line);
      p = record_all_compile_warnings_for_this_file(file_being_compiled,line,fd,fd2);
    } else {
      get_new_line = TRUE;
      continue;
    }
    if (!p) break;
    else get_new_line = FALSE;
  }
  fclose(fd);
  fclose(fd2);
}
    
      
	    

      
    

  
