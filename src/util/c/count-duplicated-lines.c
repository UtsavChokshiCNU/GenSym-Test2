
#include <stdio.h>
#include <string.h>

#define SIZE 200
#define TRUE 1
#define FALSE 0

main(argc, argv)
    int argc;
    char **argv;
{
  char line[SIZE],last[SIZE];
  int count = 0;

  last[0]='\0';

  while (1) {
  newline:
    if (NULL == gets(line)) {
      if(0<count)printf("%5d  %s\n",count,last);
      return 0;
    }
    if (0==strcmp(line,last))
      count++;
    else {
      if(0<count)printf("%5d  %s\n",count,last);
      strcpy(last,line);
      count=1;
    }
  }
}
