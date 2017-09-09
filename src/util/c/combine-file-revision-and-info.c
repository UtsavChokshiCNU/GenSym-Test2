
#include <stdio.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

int show_working_file = FALSE;
char working_file[400];

main()
{
  char line[100],ch;

  while (1) {
    if (NULL == gets(line)) return;
    if (0==strncmp("Working file: ",line,14)) {
      strcpy(working_file,&line[14]);
      show_working_file = TRUE;
    }
    if (0==strncmp("revision ",line,9))
      {int i;

      if (show_working_file) {
	printf("\n%s\n", working_file);
	show_working_file = FALSE;
      }
      for (i=9; (ch = line[i]) != '\0' && ch != ' '; i++);
      if (ch == ' ') line[i] = '\0';
      fputs(line+9,stdout);
      fputc(' ',stdout);
      if (NULL == gets(line)) return;
      puts(line);
      fflush(stdout);
      }
  }
}
