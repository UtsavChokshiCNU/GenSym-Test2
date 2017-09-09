#include <sys/types.h>
#include <sys/ioctl.h> /* for 4.3BSD alikes (AIX) */
#include <sys/stat.h>  /* For stat() function. */
#include <sys/statvfs.h>

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


/* This file defines the code needed to execute the postinstall code.
   Currently this only handles the replace_rootdir function.

   We're allowing the same thing as intel, which is dumb but consistent.
   replace_rootdir("tw2"^"bin", "envvars.sh");
   So we need to create from this: basedir/tw2/bin/envvars.sh 
   We will also accept input that just has the filename: 
   replace_rootdir(tw2/bin/envvars.sh) 
*/

/* kind of ugly: we keep a global variable to point to the current place we are
   in the input stream, in case of multiple replace_rootdir's. */
char * input_pointer;

/* Loops through the input (assumes caller has setup input_pointer) extracting a
   filename from the replace_rootdir function call, returns malloc'd buffer to
   that filename.*/
char * parse_input(char * basedir)
{
  int keep_going;
  char c, *buffer,*original_input;
  if (*input_pointer == '\0')
    return NULL;
  buffer = (char *)malloc(1024);
  bzero(buffer,1024);
  strcpy(buffer,basedir);
  original_input = input_pointer;
  if (buffer[strlen(buffer)-1] != '/')
    /* Ensure trailing slash */
    strcat(buffer,"/");
  if (!strncmp(input_pointer,"replace_rootdir(",16)) { /* 16 chars.  I counted 'em. :-) */
    /* Yay, we found the right input.
       Now loop through, copying and converting characters
       Stop when we get to semicolon or null and return the filename we've found.*/
    keep_going = 1;
    /* +=16 skips the "replace_rootdir(" part. */
    for (input_pointer+=16;keep_going;input_pointer++) {
      c = *input_pointer;
      switch (c) {
      case '\"':
      case ' ':
      case ')':
	{ /* just skip most punctuation */
	  break;
	}
      case ';':
	{ /* Done with this filename. Verify below. */
	  keep_going = 0;
	  break;
	}
      case '\0':
	{ /* Done with this filename. Verify below. */
	  keep_going = 0;
	  input_pointer--; /* back up over the null so we get it again. */
	  break;
	}
      case '^':
      case ',':
	{ /* Turn ^ and , into / */
	  strcat(buffer,"/");
	  break;
	}
      default:
	{
	  /* It would be more efficient to maintain the buffer end pointer.
	     But it would be more work :-) */
	  buffer[strlen(buffer)] = c;
	  break;
	}
      }
    }
    if (check_for_file(buffer) != 0) {
      printf("ERROR:  Cannot find postinstall input file:  %s\n",buffer);
      return NULL;
    } else {
      return buffer;
    }
  } else {
    printf("ERROR:  Found incorrect input in postinstall code:  %s\nParsed through to %s\n",original_input,input_pointer);
    return NULL;
  }
}
      

/* Here's the contents of the script we'll be running. */

char * temp_file_contents = "#!/bin/sh\n\
newroot=$2\n\
tmpfile=/tmp/gensym-sed-$$\n\
mv $1 $tmpfile\n\
sed \"s,%ROOTDIR%,$newroot,g\" $tmpfile > $1\n\
chmod 755 $1\n\
rm $tmpfile\n";

char * create_temporary_script()
{
  char* tempfile;
  int file, i;
  tempfile = (char *)malloc(1024);
  sprintf(tempfile,"/tmp/gensym-postinstall-%d",getpid());
  /* create file for write, 0755 gives execute and read access */
  file = open(tempfile,O_WRONLY|O_CREAT, 0755);
  if (file == -1) {
    perror("ERROR: cannot open temporary script file for postinstall code");
    return NULL;
  }
  if (write(file,temp_file_contents,strlen(temp_file_contents)) == -1)
    perror("ERROR: cannot write to postinstall temporary script file");
  
  if (close(file) != 0) {
    perror("ERROR: closing temporary script file for postinstall code");
  }
  return tempfile;
}
  
    
extern void execute_postinstall_step(char * input, char * basedir)
  {
    char *file,*tempscript,*command;

    /* create the script file in /tmp so we can execute it. */
    tempscript = create_temporary_script();

    /* Parse the input from the family file */
    input_pointer = input;
    while (file = parse_input(basedir)) {
      
      /* Execute the script on the input file */
      command = (char *)malloc(1024);
      sprintf(command,"%s %s %s",tempscript,file, basedir);
      system(command);
    }

    /* Done with temporary script, delete it. */
    if (unlink(tempscript) == -1)
      perror("ERROR: deleting temporary script file for postinstall code");
  }


#ifdef DO_MAIN
int
main (int argc, char *argv[])
{
char* file;
  input_pointer = "replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-j2ee\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-jboss\");replace_rootdir(\"jms\"^\"bin\", \"startjmsbridge-openjms\");";
  while (file = parse_input("/home/yduj/linux-install")) {
    printf("fussing with file %s\n",file);
  }
  /*  execute_postinstall_step(argv[1], "/home/yduj/tw2-install");*/
}
#endif
