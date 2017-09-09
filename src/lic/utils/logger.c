/******************************************************************************
 * Maintain finite set of log files of limited length.
 * Compile this:  gcc -o licencing-client licencing-client.c -Dresponse.c
 */


/******************************************************************************
logger <file-root> <size> <count>

This program will create and maintain up to <count> files.  Each of these
files will have no more than <size> lines in it.  These files will be names
from  <file-root>.N where N is 1..<count>

The contents of the files is obtained from standard input.  This is useful
for maintaining a record of the recent activities of some process that runs 
for a long time.
******************************************************************************/


/***** Module Imports *****/

#include <stdio.h>
#include <stdlib.h>

/***** Spec Module Internals *****/

static void die(int status, char* explaination);

/***** Implement *****/

static void die(status,explaination)
  int status; char* explaination;
{
  fprintf(stderr,"ERROR: %s\n", explaination);
  exit(status);
}

static void help_and_die(status,explaination)
  int status; char* explaination;
{
  fprintf(stderr," usage: logger <file-root> <size> <count>\n");
  fprintf(stderr," Creates up to <count> files named <file-root>.<N> where <N>\n");
  fprintf(stderr," runs from 1 to <count>.  The files will have <size> lines in them.\n");
  fprintf(stderr," If more space is needed the oldest file is discarded and filled\n");
  fprintf(stderr," up again becomming the newest file.  This is be used to keep\n");
  fprintf(stderr," a log of the last <size>*(<count>-1) lines appearing on standard\n");
  fprintf(stderr," input.\n");
  die(status,explaination);
}

main(argc, argv)
 int argc;
 char *argv[];
{
  if (argc!=4) help_and_die(111,"bad arguments");
  {
    char *file_root = argv[1];
    int line_count_limit = atoi(argv[2]);
    int file_count_limit = atoi(argv[3]);
    
    if(!(line_count_limit&&file_count_limit)) help_and_die(112,"bad arguments");
    while(!feof(stdin)){
      int  file_index = 0;
      for(file_index=1;
	  file_index<=file_count_limit
	    && !feof(stdin);
	  file_index++){
	char file_name[1000];
	sprintf(file_name,"%s.%d",file_root,file_index);
	{
	  int line_index;
	  FILE *stream=fopen(file_name,"w");
	  if(stream==NULL){ perror("Logfile open failed"); exit(100); };
	  for(line_index=line_count_limit;line_index;line_index--){
	    char line_buffer[1001];
	    char *input=fgets(line_buffer,1000,stdin);

	    if(input==NULL)break;
	    fputs(line_buffer,stream);
	    fflush(stream);}
	fclose(stream);}}}}}



